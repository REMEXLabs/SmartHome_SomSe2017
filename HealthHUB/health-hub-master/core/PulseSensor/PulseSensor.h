/*
Author: Nina Schaaf
Update: 29. April 2017
//--------------------------------------------------------------------------
*/

#ifndef __PULSE_H__
#define __PULSE_H__

#include "List.h"
#include "PulseSensorBPM.h"
#include "Singleton.h"
#include "SerialCommunication.h"

#include <avr/interrupt.h>
#include <avr/io.h>

// Provides a class for the pulse sensor
//
class PulseSensor : public Singleton <PulseSensor>
{
  friend class Singleton <PulseSensor>;

  public:
    ~PulseSensor () {}

    void registerSensor(int pulse_pin, unsigned long sample_interval_ms);
    void reset();
    int16_t getSensorValue();
    int16_t getSignal();

    void update();
    bool finishedScan();
    bool readSensor();
    void cachePulse();

  protected:
    PulseSensor() : BPMHistory(5), pulseDetector(0, 0) {}

  private:
    PulseSensorBPM pulseDetector;

    List BPMHistory;
};

#endif // __PULSE_H__
