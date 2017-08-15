/*
Author: Andreas Fliehr
Update: June 2, 2017
//--------------------------------------------------------------------------
*/

#include "FingerprintScanner.h"
#include "State.h"
#include "Timer.h"
#include "LedStrip.h"
#include <Arduino.h>

// Initialize the scanner by setting the pins of the scanner
// and some additional initialising commands
//
void FingerprintScanner::registerScanner(uint8_t rxPin, uint8_t txPin){
  scanner = FPS_GT511C3(rxPin, txPin);

  scanner.Open();
  if (State::getInstance().getSetupState() != SetupStates::NOT_CONNECTED){
    scanner.SetLED(true);
  }
}

// Check if a finger is pressed against the scanner
// Return: True if a finger is pressed, false if not
//
bool FingerprintScanner::checkFinger(){
  return scanner.IsPressFinger();
}

// If scan process has not been completed so far, scan the fingerprint
// Return: True if scan process was completed within this request, false if not
//
bool FingerprintScanner::update(){
  scanFingerID();
  return finishedScan();
}

// Scan the currently pressed finger and save the value
//
void FingerprintScanner::scanFingerID(){
  if(scanner.IsPressFinger()){
    scanner.CaptureFinger(false);
    fingerID = scanner.Identify1_N();
  }
}

// Check if a finger was recognized,
// Return: True if a fingerprint was recognized, false if not
//
bool FingerprintScanner::finishedScan(){
  if (fingerID < 200){
    return true;
  }

  return false;
}

// Return: The person ID if a finger was recognized, return 200 if not
//
int16_t FingerprintScanner::getSensorValue(){
  if (fingerID < 200) {
    uint8_t personID = fingerID/3+1;
    fingerID = 200;

    return personID;
  }

  return fingerID;
}

// Enroll a specific person ID to the fingerprint scanner's storage,
// therefore 3x3=9 fingerprint scans are made
//
// Code copied and modified from lib/FPS_GT511C3/Examples/FPS_Enroll/FPS_Enroll.ino
// Credit: Josh Hawley
//
void FingerprintScanner::createID(uint8_t personID){

  int8_t currentSeconds;
  int8_t previousSeconds;

  uint8_t nPID = (personID-1)*3;

  for (uint8_t id = nPID; id <= nPID+2; ++id) {
    scanner.EnrollStart(id);
    if (id == nPID) State::getInstance().setSetupState(SetupStates::FIRST_SCAN_1);
    if (id == nPID+1) State::getInstance().setSetupState(SetupStates::SECOND_SCAN_1);
    if (id == nPID+2) State::getInstance().setSetupState(SetupStates::THIRD_SCAN_1);
    previousSeconds = Timer::getInstance().seconds();
    LedStrip::getInstance().updateLight();
    while(scanner.IsPressFinger() == false){
      currentSeconds = Timer::getInstance().seconds();
      if (currentSeconds - previousSeconds >= 10){
        State::getInstance().setSetupState(SetupStates::SETUP_TIMEOUT);
        removeID(personID);
        return;
      }
    }

    bool hqScan = scanner.CaptureFinger(true);
    int iret = 0;
    if (hqScan != false){
      State::getInstance().setSetupState(SetupStates::REMOVE_FINGER);
      scanner.Enroll1();
      while(scanner.IsPressFinger() == true) Timer::getInstance().delayMilliseconds(100);
      if (id == nPID) State::getInstance().setSetupState(SetupStates::FIRST_SCAN_2);
      if (id == nPID+1) State::getInstance().setSetupState(SetupStates::SECOND_SCAN_2);
      if (id == nPID+2) State::getInstance().setSetupState(SetupStates::THIRD_SCAN_2);
      previousSeconds = Timer::getInstance().seconds();
      LedStrip::getInstance().updateLight();
      while(scanner.IsPressFinger() == false){
        currentSeconds = Timer::getInstance().seconds();
        if (currentSeconds - previousSeconds >= 10){
          State::getInstance().setSetupState(SetupStates::SETUP_TIMEOUT);
          removeID(personID);
          return;
        }
      }

      hqScan = scanner.CaptureFinger(true);
      if (hqScan != false){
        State::getInstance().setSetupState(SetupStates::REMOVE_FINGER);
        scanner.Enroll2();
        while(scanner.IsPressFinger() == true) Timer::getInstance().delayMilliseconds(100);
        if (id == nPID) State::getInstance().setSetupState(SetupStates::FIRST_SCAN_3);
        if (id == nPID+1) State::getInstance().setSetupState(SetupStates::SECOND_SCAN_3);
        if (id == nPID+2) State::getInstance().setSetupState(SetupStates::THIRD_SCAN_3);
        previousSeconds = Timer::getInstance().seconds();
        LedStrip::getInstance().updateLight();
        while(scanner.IsPressFinger() == false){
          currentSeconds = Timer::getInstance().seconds();
          if (currentSeconds - previousSeconds >= 10){
            State::getInstance().setSetupState(SetupStates::SETUP_TIMEOUT);
            removeID(personID);
            return;
          }
        }

        hqScan = scanner.CaptureFinger(true);
        if (hqScan != false){
          State::getInstance().setSetupState(SetupStates::REMOVE_FINGER);
          iret = scanner.Enroll3();
          if (iret == 0){
            if (id == nPID) State::getInstance().setSetupState(SetupStates::FIRST_SCAN_SUCCESS);
            if (id == nPID+1) State::getInstance().setSetupState(SetupStates::SECOND_SCAN_SUCCESS);
            if (id == nPID+2) State::getInstance().setSetupState(SetupStates::THIRD_SCAN_SUCCESS);
          } else {
            if (id == nPID) State::getInstance().setSetupState(SetupStates::ERROR_FIRST_SCAN);
            if (id == nPID+1) State::getInstance().setSetupState(SetupStates::ERROR_SECOND_SCAN);
            if (id == nPID+2) State::getInstance().setSetupState(SetupStates::ERROR_THIRD_SCAN);
            id = id-1;
          }
        } else {
          State::getInstance().setSetupState(SetupStates::ERROR_FINGER_3);
          id = id-1;
        }
      } else {
        State::getInstance().setSetupState(SetupStates::ERROR_FINGER_2);
        id = id-1;
      }
    } else {
      State::getInstance().setSetupState(SetupStates::ERROR_FINGER_1);
      id = id-1;
    }
  }
  State::getInstance().setSetupState(SetupStates::SETUP_DONE);
}

// Remove a specific person ID from the fingerprint scanner's storage
//
void FingerprintScanner::removeID(uint8_t personID){
  for (uint8_t id = (personID-1)*3; id <= (personID-1)*3+2; ++id) {
    scanner.DeleteID(id);
  }
  State::getInstance().setSetupState(SetupStates::SETUP_DONE);
}

// Remove all stored fingerprints
//
void FingerprintScanner::removeAllIDs(){
  scanner.DeleteAll();
  State::getInstance().setSetupState(SetupStates::SETUP_DONE);
}

// An action handler for the fingerprint scanner's setup
//
uint8_t FingerprintScanner::actionHandler(uint8_t setupState, uint8_t personID){

  switch (setupState) {
    case SetupStates::SETUP_START:
      removeID(personID);
      createID(personID);
      return SetupStates::SETUP_IDLE;
    case SetupStates::DELETE:
      removeID(personID);
      return SetupStates::SETUP_IDLE;
    case SetupStates::RESET:
      removeAllIDs();
      return SetupStates::SETUP_IDLE;
  }
}
