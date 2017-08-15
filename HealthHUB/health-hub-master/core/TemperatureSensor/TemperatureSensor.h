/*
Author: Eric Schmidt
Update: 22. April 2017
//--------------------------------------------------------------------------
*/

#ifndef __TEMP_H__
#define __TEMP_H__

#include "List.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "Singleton.h"

// Provides a class for the temperature sensor
//
class TemperatureSensor : public Singleton <TemperatureSensor>
{
  friend class Singleton <TemperatureSensor>;

  public:
    ~TemperatureSensor () {}

    void registerSensor(uint8_t roomSensorPin, uint8_t fingerSensorPin);
    void update();
    void reset();
    bool finishedScan();
    int16_t getSensorValue();

  protected:
    TemperatureSensor() : fingerTempHistory(5), fingerTemp(0), roomTemp(0) {}

  private:
    DallasTemperature sensorFinger;
    DallasTemperature sensorRoom;

    OneWire fingerTemp;
    OneWire roomTemp;


    List fingerTempHistory;

    int16_t roomTempMean   = 0;
    int16_t errorValue     = -12700;
    bool isFinishedScan      = false;

    void requestRoomTemperature();
    void requestFingerTemperature();
    int16_t fingerTemp2bodyTemp(int16_t fingerTemperature, int16_t roomTempMean);
};

#endif // __TEMP_H__
