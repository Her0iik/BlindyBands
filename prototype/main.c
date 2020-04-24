#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIX 2	 // input pin Neopixel is attached to
#define PIN_TRIG_CAPTEUR_ULTRA 3
#define PIN_ECHO_CAPTEUR_ULTRA 3
#define PIN_POTENTIOMETRE 5
#define NUMPIXELS 12 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_NEOPIX, NEO_GRB + NEO_KHZ800);

int delayval = 100; // timing delay in milliseconds
int cm = 0;
int objectivAngle = 180;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;
bool guidageStarted = false;

char message[6] = {' ',' ',' ',' ',' ','\0'};
int i = 0;

void setup() {
  // Initialize the NeoPixel library.
  pixels.begin();
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  
}

void loop() {
  // measure the ping time in cm
  // cm = 0.01723 * readUltrasonicDistance(PIN_TRIG_CAPTEUR_ULTRA, PIN_ECHO_CAPTEUR_ULTRA);
  
  
  
  setColor();
  int data = digitalRead(8);
  if(data == 1 || guidageStarted){
    if(guidageStarted == false){
      pixels.setPixelColor(0, pixels.Color(255,255,0));
      delay(1000);
    }
    guidageStarted = true;
  	int dataAngle = readData();
    if(dataAngle != 0){
      objectivAngle = objectivAngle + dataAngle;
    }
    //Serial.println(objectivAngle);
    checkAngle(objectivAngle);
  }
  //delay(500);
  
}

// setColor()
// picks random values to set for RGB
void setColor(){
  redColor = 0;//random(0, 255);
  greenColor = 255;//random(0,255);
  blueColor = 0;//random(0, 255);
}

void checkAngle(int expectedAngle){
  int delta = 20;
  int sensorValue = analogRead(A1);
  int angle = sensorValue * (360.0 / 1023.0);
  //Serial.println(angle);
  if(angle > expectedAngle + delta && digitalRead(7) == 0){
    //Serial.println("Gauche");
    printPixels(angle-expectedAngle);
  }else if(angle < expectedAngle - delta && digitalRead(7) == 1){
    //Serial.println("Droite");
    printPixels(expectedAngle - delta);
  } else {
    //Serial.println("ok");
    printPixels(0);
  }
}

void printPixels(int delta){
  int step = 180 / NUMPIXELS;
  for(int i=0; i < NUMPIXELS; i++) {
    if(i < delta/step){
      pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
    }else{
      pixels.setPixelColor(i, pixels.Color(0,0,0));
    }
    // This sends the updated pixel color to the hardware.
    pixels.show();

    // Delay for a period of time (in milliseconds).
    //delay(delayval);
  }
}

void checkObstacle(int delta){
  cm = 0.01723 * readUltrasonicDistance(PIN_TRIG_CAPTEUR_ULTRA, PIN_ECHO_CAPTEUR_ULTRA);
  int step = 335 / 12;
  for(int i=0; i < NUMPIXELS; i++) {
    //Serial.println(i);
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    if(i < cm/step){
      pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
    }else{
      pixels.setPixelColor(i, pixels.Color(0,0,0));
    }
    // This sends the updated pixel color to the hardware.
    pixels.show();

    // Delay for a period of time (in milliseconds).
    //delay(delayval);
  }
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

int readData() {
  char chaineVide[6] = {' ',' ',' ',' ',' ','\0'};

  if(Serial.available() > 0) {
    char incomingByte = Serial.read();
    message[i] = incomingByte;
    i++;
  }
  
  if(i == 5) {
    message[5] = '\0';
    int res = atoi(message);
    strcpy(message, chaineVide);
    i = 0;
    return res;
  }
  
  return 0;
}