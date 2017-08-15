/*
Author: Theresa Denhard
Update: 30. Mai 2017
//--------------------------------------------------------------------------
*/
#include "LedStrip.h"

// Register LedStrip by setting the pin
void LedStrip::registerSensor(uint8_t ledStripPin){
  strip = Adafruit_NeoPixel(60, ledStripPin, NEO_GRB + NEO_KHZ800);
  reset();
}

//change light effect with different state
void LedStrip::updateLight(){
  statusScan = State::getInstance().getScanState();
  statusSetup = State::getInstance().getSetupState();

//eather scan modus or registration of fingerprint is active
  if(statusScan!=lastScanState){
      lastScanState=statusScan;
      scanActive=true;
      registerActive=false;
  }
  else if(statusSetup!=lastSetupState){
      lastSetupState=statusSetup;
      scanActive=false;
      registerActive=true;

  }

  if(scanActive){
      switch (statusScan)
      {
         case 0:
            lightOn();
            break;
         case 1:
            startScan();
            break;
         case 2:
              finishScan();
         case 3:
            scanError();
         default:
          reset();
      }
    }


    if(registerActive){
        lightOn();
        switch (statusSetup)
        {
          case 11:
            setLedByNumber(0);
            break;
          case 12:
            setLedByNumber(7);
            break;
          case 13:
            setLedByNumber(14);
            break;
          case 21:
            setLedByNumber(21);
            break;
          case 22:
            setLedByNumber(28);
            break;
          case 23:
            setLedByNumber(35);
            break;
          case 31:
            setLedByNumber(42);
            break;
          case 32:
            setLedByNumber(49);
            break;
          case 33:
            setLedByNumber(56);
            break;
          default:
            reset();
        }
  }


}

//function for INIT=basic light, brightness to 10 percent
void LedStrip::lightOn(){
  strip.begin();
  for(uint16_t i=0; i<60; i++) {
      strip.setBrightness(10);
      strip.setPixelColor(i, white);
  }

  strip.show();
}


//function for Scan mode
void LedStrip::startScan(){
  if(brightness==10){//first call
    lightOn();
  }
  unsigned long currentMillis=timer.millis();
  if(currentMillis-previousMillis>=intervall){//increase brightness
      if(scanControl!=0){
        strip.setBrightness(brightness);
        strip.show();
        previousMillis=currentMillis;
        brightness++;
      }
      if(brightness==100||scanControl==0){//reduce brightness
          scanControl=0;
          brightness--;
          strip.setBrightness(brightness);
          strip.show();
          previousMillis=currentMillis;
          if(brightness==10){
            scanControl=1;
          }
        }
  }
}//end of startScan()


void LedStrip::finishScan(){
  lightOn();
}


//SSCAN ERROR
void LedStrip::scanError(){
  lightOn();
  if(errorControl<10){
    for(uint8_t j=0;j<10;j++){
      for(uint16_t i=0; i<60; i++) {
        strip.setPixelColor(i, Wheel());
        strip.show();
        errorControl++;
      }
    }
  }else
    reset();
    lightOn();
}

uint32_t LedStrip::Wheel() {
  strip.setBrightness(10);
  red=red-1;
  green=green-1;
  blue=blue-1;
  return strip.Color(red,green,blue);
}

void LedStrip::setLedByNumber(uint16_t numPixels){

  strip.begin();

  for(uint16_t i=0; i<numPixels; i++) {
      strip.setBrightness(10);
      strip.setPixelColor(i, green);
  }
  strip.show();

 /*unsigned long currentMillis =timer.millis();//new
    if(currentMillis-previousMillis>=intervall&&registerControl!=0){
      Serial.println("insider Timer if-Schleife");
      previousMillis=currentMillis;
        for(uint16_t i=0; i<numPixels; i++){
            strip.setPixelColor(i, green);
            red=red-1;
            green=green-1;
            blue=blue-1;
            strip.Color(red,green,blue);
            if(pixel==numPixels-1){
              registerControl=0;
            }
            else if(i==numPixels-1){
                strip.show();
                pixel++;
            }
        }
    }*/
}

//after an error occured, reset all variables of class LED-strip
void LedStrip::reset(){
  white = strip.Color(255,255,255);
  red = strip.Color(255,0,0);
  green = strip.Color(0,255,0);
  blue = strip.Color(0,0,255);

  brightness=10;//standard brightness to 10 percent
  scanControl=1;//controls light dimming while scan-modus
  if(statusScan!=3){//not accessing if an error occured
    errorControl=0;//error light effect control - interrupts effect
  }
  registerControl=1;
  pixel=0;//start pixel on registration
  lastScanState=0;//to check if ScanState changed
  lastSetupState=0;//to check if SetupState changed
  scanActive=0;//equal 1 switch to scan-modus functions within updateLight() function
  registerActive=0;//equal 1 switch to register fingerprint functions within updateLight() function

  lightOn();
}
