/*
Author: Mario Walz
Update: 28. April 2017
//--------------------------------------------------------------------------
*/

#ifndef __GSR_H__
#define __GSR_H__

#include "List.h"
#include "Singleton.h"
#include "ADCHandler.h"

// Provides a class for the temperature sensor
//
class GSRSensor : public Singleton <GSRSensor>
{
  friend class Singleton <GSRSensor>;

  public:
    ~GSRSensor () { }

    void registerSensor(uint8_t sensorPin);
    void update();
    void reset();
    bool finishedScan();
    int16_t getSensorValue();

  protected:
    GSRSensor() : gsrHistory(5) {}

  private:
    List gsrHistory;
    ADCHandler adcHandler;

    bool isFinishedScan = false;
    uint8_t sensorPin;

    void requestGSR();
};

#endif // __GSR_H__
