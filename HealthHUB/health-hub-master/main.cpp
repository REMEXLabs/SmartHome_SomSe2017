#include "Pins.h"
#include "State.h"
#include "Timer.h"
#include "TemperatureSensor.h"
#include "FingerprintScanner.h"
#include "PulseSensor.h"
#include "GSRSensor.h"
#include "SerialCommunication.h"
#include "LedStrip.h"

#include <string.h>
#include <Arduino.h>

using namespace std;

void handleTemperature(){
  if (!TemperatureSensor::getInstance().finishedScan()){
    TemperatureSensor::getInstance().update();
    if (TemperatureSensor::getInstance().finishedScan()){
      int16_t bodyTemp = TemperatureSensor::getInstance().getSensorValue();
      SerialCommunication::getInstance().sendData(-1, -1, bodyTemp, -1);
    }
  }
}

void handlePulse(){
  if (!PulseSensor::getInstance().finishedScan()){
    PulseSensor::getInstance().update();
    if (PulseSensor::getInstance().finishedScan()){
      int16_t pulse = PulseSensor::getInstance().getSensorValue();
      SerialCommunication::getInstance().sendData(-1, pulse, -1, -1);
    }
  }
}

void handlePulseStream(){
  if (!PulseSensor::getInstance().finishedScan()){
    int16_t signal = PulseSensor::getInstance().getSignal();
    SerialCommunication::getInstance().sendStream(0, signal);
  }
}

void handleGSR(){
  if (!GSRSensor::getInstance().finishedScan()){
    GSRSensor::getInstance().update();
    if (GSRSensor::getInstance().finishedScan()){
      int16_t gsr = GSRSensor::getInstance().getSensorValue();
      SerialCommunication::getInstance().sendData(-1, -1, -1, gsr);
    }
  }
}

int main(void)
{
  Serial.begin(9600);

  PulseSensor::getInstance().registerSensor(PULSE_PIN, 2L);
  TemperatureSensor::getInstance().registerSensor(ROOM_TEMP_PIN, FINGER_TEMP_PIN);
  GSRSensor::getInstance().registerSensor(GSR_PIN);
  FingerprintScanner::getInstance().registerScanner(FPS_RX_PIN, FPS_TX_PIN);
  LedStrip::getInstance().registerSensor(LED_STRIP_PIN);

  uint8_t personID = 1;
  int16_t setupCmd = -1;

  uint16_t previousMillis = 0;
  uint16_t previousMillis_pulsestream = 0;
  uint16_t previousSeconds = 0;
  int16_t previousSeconds_timeout = 0;

  bool tmp_checkFinger = false;
  int8_t previous_finger = 0;

  while(1) {
    LedStrip::getInstance().updateLight();

    uint16_t currentMillis = Timer::getInstance().millis();
    uint16_t currentSeconds = Timer::getInstance().seconds();

    uint8_t currentScanState = State::getInstance().getScanState();
    uint8_t currentSetupState = State::getInstance().getSetupState();

    if (currentSetupState != SetupStates::SETUP_IDLE && currentSetupState != SetupStates::NOT_CONNECTED){
      uint8_t state = FingerprintScanner::getInstance().actionHandler(currentSetupState, personID);
      State::getInstance().setSetupState(state);
    }

    if(currentScanState == ScanStates::IDLE && currentSetupState != SetupStates::NOT_CONNECTED){
      if (FingerprintScanner::getInstance().checkFinger() != tmp_checkFinger) previous_finger = currentSeconds;
      if(FingerprintScanner::getInstance().checkFinger()){
        if (FingerprintScanner::getInstance().update()){
          personID = FingerprintScanner::getInstance().getSensorValue();

          State::getInstance().setScanState(ScanStates::START);
          SerialCommunication::getInstance().sendData(personID, -1, -1, -1);

          previousMillis = currentMillis;
          previousMillis_pulsestream = currentMillis;
          previousSeconds = currentSeconds;
          previousSeconds_timeout = currentSeconds;
        }

        Serial.println(currentSeconds - previous_finger);
        if (currentSeconds - previous_finger >= 6) {
          personID = -1;

          State::getInstance().setScanState(ScanStates::START);
          SerialCommunication::getInstance().sendData(personID, -1, -1, -1);

          previousMillis = currentMillis;
          previousMillis_pulsestream = currentMillis;
          previousSeconds = currentSeconds;
          previousSeconds_timeout = currentSeconds;
        }
      }
      tmp_checkFinger = FingerprintScanner::getInstance().checkFinger();
    }

    if (currentScanState == ScanStates::START){
      if (currentMillis - previousMillis >= 2){
        previousMillis = currentMillis;
        handlePulse();
      }

      if (currentSeconds - previousSeconds >= 1) {
        previousSeconds = currentSeconds;
        handleTemperature();
        handleGSR();
      }

      if (currentSeconds - previousSeconds_timeout >= 60){
        previousSeconds_timeout = currentSeconds;
        State::getInstance().setScanState(ScanStates::TIMEOUT);
        Serial.println("SCAN TIMEOUT");
      }

      if (currentMillis - previousMillis_pulsestream >= 180){
        previousMillis_pulsestream = currentMillis;
        handlePulseStream();
        Serial.println("180");
      }

      if ((TemperatureSensor::getInstance().finishedScan() && GSRSensor::getInstance().finishedScan() && PulseSensor::getInstance().finishedScan())){
        Serial.println("ALL SCANS FINISHED!");
        State::getInstance().setScanState(ScanStates::FINISHED);
        SerialCommunication::getInstance().sendData(personID, PulseSensor::getInstance().getSensorValue(), TemperatureSensor::getInstance().getSensorValue(), GSRSensor::getInstance().getSensorValue());
      }
    }

    if (currentScanState == ScanStates::IDLE){
      setupCmd = SerialCommunication::getInstance().checkSetup();
      if (setupCmd != -1) {
        Serial.print("setupCmd: ");
        Serial.println(setupCmd);
        personID = setupCmd;
        State::getInstance().setSetupState(SetupStates::SETUP_START);
      }
    }

    if ((currentScanState == ScanStates::TIMEOUT) || (currentScanState == ScanStates::FINISHED)){
      if(!FingerprintScanner::getInstance().checkFinger()){
        PulseSensor::getInstance().reset();
        TemperatureSensor::getInstance().reset();
        GSRSensor::getInstance().reset();
        State::getInstance().setScanState(ScanStates::IDLE);
      }
    }

  }

  return 0;
}
