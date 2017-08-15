/*
Author: Nina Schaaf
Update: 12. May 2017
//--------------------------------------------------------------------------
*/

#include "PulseSensor.h"

void PulseSensor::registerSensor(int pulse_pin, unsigned long sample_interval_ms){
  PulseSensorBPM pulseDetector(pulse_pin, sample_interval_ms);
  this->pulseDetector = pulseDetector;
}

void PulseSensor::update(){
  if (readSensor()) {
    cachePulse();
  }
}

/*-------------------------------------------------------

  Caches the current BPM
  Make sure the pulse-value itself is a realistic value (30-200),
  then check if the BPMCache is completely filled up

  If
  a) true:
  Check the standardDeviation of the values
  (to prevent adding values which were recorded in running idle: these values scatter highly) .
  then either add the mean of the Cache-Values to the BPM History
  or in case of high standardDeviation drop the values
  b) false:
  add the current bpm-value to the cache

---------------------------------------------------------*/
void PulseSensor::cachePulse(){
  int pulse = pulseDetector.getBPM();

  if ( 30 < pulse && pulse < 200) {
      BPMHistory.push_front(pulse);
  }
}

// Return: The calculated pulse (depends on the BPM History)
int16_t PulseSensor::getSensorValue(){
  return BPMHistory.mean();
}

int16_t PulseSensor::getSignal(){
  int16_t signal = pulseDetector.getSignal();
  return signal;
}

// Reset the Pulse value history
void PulseSensor::reset(){
  BPMHistory.clear();
}

/*-------------------------------------------------------

  Decides if the current scan has finished by calculating the standardDeviation
  deviation and check it against a given threshold.

  Return: True if scan has finished. False if scan has not finished.

---------------------------------------------------------*/
bool PulseSensor::finishedScan(){
  uint8_t threshold = 10;

  if (BPMHistory.size() == BPMHistory.max_size()){
    if(BPMHistory.standardDeviation() < threshold){
      return true;
    }
  }

  return false;
}

// Read the analog signal. Function returns true if a heartbeat was detected
bool PulseSensor::readSensor()
{
  return pulseDetector.readSensor();
}
