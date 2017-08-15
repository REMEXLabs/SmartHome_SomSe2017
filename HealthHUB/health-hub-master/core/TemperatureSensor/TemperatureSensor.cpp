/*
Author: Eric Schmidt
Update: 22. April 2017
//--------------------------------------------------------------------------
*/
#include "TemperatureSensor.h"

// Register sensor by setting the pins for the room & finger temperature sensor
//
void TemperatureSensor::registerSensor(uint8_t roomSensorPin, uint8_t fingerSensorPin){
  fingerTemp = OneWire(fingerSensorPin);
  roomTemp = OneWire(roomSensorPin);

  sensorFinger = DallasTemperature(&fingerTemp);
  sensorRoom =  DallasTemperature(&roomTemp);

  sensorRoom.begin();
  sensorFinger.begin();
}

// Request the current room temperature and save the value
//
void TemperatureSensor::requestRoomTemperature(){
  sensorRoom.setOneWire(&roomTemp);

  sensorRoom.requestTemperatures();
  int16_t sensorValue = round(sensorRoom.getTempCByIndex(0) * 100);
  if (sensorValue != errorValue){
    roomTempMean = sensorValue;
  }else{
    //Send Message to Raspberry Log that Sensor is broken
  }
}

// Request the current finger temperature and save the value into a chained list
//
void TemperatureSensor::requestFingerTemperature(){
  sensorRoom.setOneWire(&fingerTemp);

  sensorFinger.requestTemperatures();
  int16_t sensorValue = round(sensorFinger.getTempCByIndex(0) * 100);
  if (sensorValue != errorValue){
    fingerTempHistory.push_front(sensorValue);
  }else{
    //Send Message to Raspberry Log that Sensor is broken
  }
}

// Initialize the temperature scan by requesting the room and finger temperature.
//
// Return: True if scan has finished, False if not
//
void TemperatureSensor::update(){
  requestRoomTemperature();
  requestFingerTemperature();
}

// Read the current finger temperature
//
// Return: The current finger temperature.
//
int16_t TemperatureSensor::getSensorValue(){
  return fingerTemp2bodyTemp(fingerTempHistory.read_front(), roomTempMean);
}

//Convert finger temperature to body temperature by applying linear Regression
//
// int16_t fingerTemperature: The finger temperature
//
// Return: The computed body temperature
int16_t TemperatureSensor::fingerTemp2bodyTemp(int16_t fingerTemp, int16_t roomTempMean){
  int32_t finger_coef = 8;
  int32_t room_coef = -6;
  int32_t interception = 354429;

  int32_t result = (interception + (fingerTemp * finger_coef) + (roomTempMean * room_coef)) / 100;

  return result;
}

// Decides if the current scan has finished by calculating the standardDeviation
// deviation and check it against a given threshold.
//
// Return: True if scan has finished. False if scan has not finished.
//
bool TemperatureSensor::finishedScan(){
  uint8_t deviationThreshold = 4;
  uint8_t roomThreshold = 20;

  if (!isFinishedScan){
    if (fingerTempHistory.size() == fingerTempHistory.max_size()){
      if (fingerTempHistory.standardDeviation() < deviationThreshold){
        if (fingerTempHistory.read_front() - roomTempMean > roomThreshold){
          isFinishedScan = true;
        }
      }
    }
  }

  return isFinishedScan;
}

// Clear the finger temperature history
//
void TemperatureSensor::reset(){
  fingerTempHistory.clear();
  isFinishedScan = false;
}
