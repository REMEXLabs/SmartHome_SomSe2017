/*
Author: Mario Walz
Update: 28. April 2017
//--------------------------------------------------------------------------
*/

#include "GSRSensor.h"

// Register sensor by setting the pin
//
void GSRSensor::registerSensor(uint8_t sensorPin){
  this->sensorPin = sensorPin;
  adcHandler = ADCHandler();
}

// Request the current skin resistance
//
void GSRSensor::requestGSR(){
  int sensorVal = adcHandler.ADC_Read(sensorPin);

  gsrHistory.push_front(sensorVal);
}

void GSRSensor::update(){
  requestGSR();
}

// Read the current skin resistance
//
// Return: The current skin resistance.
//
int16_t GSRSensor::getSensorValue(){
  return gsrHistory.read_front();
}

// Decides if the current scan has finished by calculating the standardDeviation
// deviation and check it against a given threshold.
//
// Return: True if scan has finished. False if scan has not finished.
//
bool GSRSensor::finishedScan(){
  uint8_t threshold = 50;

  if (!isFinishedScan){
    if (gsrHistory.size() == gsrHistory.max_size()){
      if(gsrHistory.standardDeviation() < threshold){
        isFinishedScan = true;
      }
    }
  }

  return isFinishedScan;
}

// Clear the GSR history
//
void GSRSensor::reset(){
  gsrHistory.clear();
  isFinishedScan = false;
}
