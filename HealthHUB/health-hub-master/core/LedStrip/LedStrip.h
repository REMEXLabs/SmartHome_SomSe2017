/*
Author: Theresa Denhard
Update: 29. Mai 2017
//--------------------------------------------------------------------------
*/

#ifndef __LED_H__
#define __LED_H__

#include "Adafruit_NeoPixel.h"
#include "Timer.h"
#include "State.h"
#include "Singleton.h"

using namespace ScanStates;
using namespace SetupStates;

class LedStrip : public Singleton <LedStrip>
{
  friend class Singleton <LedStrip>;

  public:
    ~LedStrip () {}

    void registerSensor(uint8_t ledStripPin); //allocate PIN
    void updateLight(); //set light effect

  protected:
      LedStrip() {};

  private:
    Adafruit_NeoPixel strip;
    Timer& timer = Timer::getInstance();
    State& state = State::getInstance();

    uint32_t white;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    uint8_t statusScan;
    uint8_t statusSetup;
    uint16_t brightness=10;//standard brightness to 10 percent
    uint8_t scanControl=1;//controls light dimming while scan-modus
    uint8_t errorControl=0;//error light effect control - interrupts effect
    uint8_t registerControl=1;
    uint8_t pixel=0;//start pixel on registration
    uint8_t lastScanState=0;//to check if ScanState changed
    uint8_t lastSetupState=0;//to check if SetupState changed
    bool scanActive=false;//equal 1 switch to scan-modus functions within updateLight() function
    bool registerActive=false;//equal 1 switch to register fingerprint functions within updateLight() function
    unsigned long intervall=10;//defines the interrupt during scan modus
    unsigned long previousMillis=0;//defines the interrupt during scan modus

    void lightOn();//basic light
    void startScan();//light effect while scan modus
    void scanError();//light effect if an error occures
    uint32_t Wheel();//function to make light effect for error mode
    void finishScan();//back to standard light
    void setLedByNumber(uint16_t numPixels);
    void reset();//reset parameter: controller and color variables
};

#endif // __LED_H__
