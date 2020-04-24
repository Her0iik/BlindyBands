import { Component, OnInit } from '@angular/core';
// import { BluetoothSerial } from '@ionic-native/bluetooth-serial';
import { SpeechRecognition } from '@ionic-native/speech-recognition/ngx';
import { Geolocation, Geoposition } from '@ionic-native/geolocation/ngx';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage {

  private currentCity;
  private userLocation: number[];
  private targetLocation: number[];
  private route;
  private mapboxToken = 'pk.eyJ1IjoibGV4b2RldiIsImEiOiJjazljdWN1d3AwN3B3M2dua3h6c3JxMGEzIn0.JsBfwTRuqyrdXxBIWQyDBA';

  constructor(
    // private bluetoothSerial: BluetoothSerial,
    private speechRecognition: SpeechRecognition,
    private geo: Geolocation,
    private http: HttpClient
  ) {}

  async getAddressBySpeech() {
    return this.speechRecognition.hasPermission()
    .then((hasPermission: boolean) => {
      if (hasPermission === false) {
        return this.speechRecognition.requestPermission();
      }

      return null;
    })
    .then(() => {
      return this.startSpeechRecognition();
    })
    .then((matches: string[]) => {
      return this.getGeocodeFromAddress(matches[0]);
    })
    .then(() => {
      return this.getCurrentLocation();
    })
    .then(() => {
      return this.getRoute(this.userLocation, this.targetLocation);
    })
    .catch((onerror) => console.log('error:', onerror));
  }

  async startSpeechRecognition() {
    return new Promise((resolve) => {
      this.speechRecognition.startListening({
        language: 'fr_FR',
        matches: 1
      })
      .subscribe(
        (matches: string[]) => resolve(matches),
        (onerror) => console.log('error:', onerror)
      );
    });
  }

  async getGeocodeFromAddress(address: string) {
    console.log(address);
    // tslint:disable-next-line: max-line-length
    return this.http.get(`https://api.mapbox.com/geocoding/v5/mapbox.places/${encodeURIComponent(address)}.json?language=fr&country=FR&access_token=${this.mapboxToken}`)
      .toPromise()
      .then((location: any) => {
        this.targetLocation = [location.features[0].center[1], location.features[0].center[0]];
        console.log('target');
        console.log(this.targetLocation);
      });
  }

  async getCurrentLocation() {
    return this.geo.getCurrentPosition({
      enableHighAccuracy: true,
      timeout: 3000
    })
      .then((resp: Geoposition) => {
        this.userLocation = [resp.coords.latitude, resp.coords.longitude];
        console.log('current');
        console.log(this.userLocation);
      }).catch((error) => {
        console.log('Error getting location', error);
      });

    /*return new Promise((resolve, reject) => {
      return this.geo.getCurrentPosition()
        .then((location: any) => {
          this.userLocation = [location.coords.longitude, location.coords.latitude];

          resolve();
        });
    });*/
  }

  async getRoute(startCoords: number[], endCoords: number[]) {
    // tslint:disable-next-line: max-line-length
    return this.http.get(`https://api.mapbox.com/directions/v5/mapbox/walking/${startCoords[0]},${startCoords[1]};${endCoords[0]},${endCoords[1]}?steps=true&access_token=${this.mapboxToken}`)
      .toPromise()
      .then((route) => {
        console.log(route);
        this.route = route;
      });
  }

  /*
  async sendViaBluetooth() {
    if (await this.bluetoothSerial.isConnected() === true) {
      this.bluetoothSerial.write([1000, 90, 0, 0, 0, 0, 0, -30, 0, 0, 0, -18, 1001])
      .then((success) => {
        console.log(success);
      })
      .catch((failure) => {
        console.log(failure);
      });
    }
  }
  */
}
