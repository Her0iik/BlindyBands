import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { IonicModule } from '@ionic/angular';
import { FormsModule } from '@angular/forms';
import { SpeechRecognition } from '@ionic-native/speech-recognition/ngx';
import { Geolocation } from '@ionic-native/geolocation/ngx/index';
import { NativeGeocoder } from '@ionic-native/native-geocoder/ngx/index';
import { HttpClientModule } from '@angular/common/http';

import { HomePage } from './home.page';
import { HomePageRoutingModule } from './home-routing.module';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    HttpClientModule,
    HomePageRoutingModule
  ],
  providers: [
    SpeechRecognition,
    Geolocation,
    NativeGeocoder
  ],
  declarations: [HomePage]
})
export class HomePageModule {}
