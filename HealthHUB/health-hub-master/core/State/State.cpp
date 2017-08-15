/*
Author: Eric Schmidt
Update: 14. Mai 2017
//--------------------------------------------------------------------------
*/

#include "State.h"
#include "Arduino.h"
#include "SerialCommunication.h"


void State::setScanState(uint8_t state){
  scanState = state;
  SerialCommunication::getInstance().setState(state);
  Serial.print("ScanState: ");
  Serial.println(scanState);
}

uint8_t State::getScanState(){
  return scanState;
}

void State::setSetupState(uint8_t state){
  setupState = state;
  Serial.print("SetupState: ");
  Serial.println(setupState);
}

uint8_t State::getSetupState(){
  return setupState;
}
