/*
Author: David Bochan
Update: 6. Juni 2017
//--------------------------------------------------------------------------
*/

#include "SerialCommunication.h"

#include <stdio.h>
#include <string.h>

/*
PARTS:
HH to initialize a new message
MESSAGE tells the type of the message (DATA, STATE)
\n shows the end of a message

EXAMPLE DATA MESSAGE:
HHMESSAGEDATAID3HEARTRATE82TEMP19GSR192\n

EXAMPLE STATE MESSAGE:
HHMESSAGESTATEVALUE1\n
*/

// Description: function to send sensor data over a serial port, e.g. to communicate it to a Raspberry Pi.
// Return: true if data was sent.
bool SerialCommunication::sendData(int16_t id, int16_t heartrate, int16_t temp, int16_t gsr){

    Serial.print(F("HHMESSAGEDATA"));

    if (id != -1){
        Serial.print(F("ID"));
        Serial.print(id);
    }
    if (heartrate != -1){
        Serial.print(F("HEARTRATE"));
        Serial.print(heartrate);
    }
    if (temp != -1){
        Serial.print(F("TEMP"));
        Serial.print(temp);
    }
    if (gsr != -1){
        Serial.print(F("GSR"));
        Serial.print(gsr);
    }

    Serial.println();

    // DEBUG ONLY
    // Serial.println(freeRam());

    return true;
}

// Description: function to send raw pulse stream over a serial port (see Config.h for available sensor values).
// Return: true if data was sent.
bool SerialCommunication::sendStream(int16_t sensor, int16_t signal){

    Serial.print(F("HHMESSAGESTREAM"));

    if (sensor != -1){
        Serial.print(F("SENSOR"));
        Serial.print(sensor);
    }
    if (signal != -1){
        Serial.print(F("SIGNAL"));
        Serial.print(signal);
    }

    Serial.println();

    return true;
}

// Description: function to send a error signal over a serial port.
// Return: true if error was sent.
bool SerialCommunication::setError(int16_t sensor){

    Serial.print(F("HHMESSAGEERROR"));

    if (sensor != -1){
        Serial.print(F("SENSOR"));
        Serial.print(sensor);
    }

    Serial.println();

    return true;
}

// Description: function to change the current state of health hub (see State.h for available states).
// Return: true if state was sent.
bool SerialCommunication::setState(uint8_t state){

    Serial.print(F("HHMESSAGESTATE"));

    if (state != -1){
        Serial.print(F("VALUE"));
        Serial.print(state);
    }

    Serial.println();

    return true;
}

char inData[20];
char inChar = -1;
byte index = 0;

bool SerialCommunication::checkSerial(char* comp) {

    while (Serial.available() > 0) {
        if (index < 19){
            inChar = Serial.read();
            inData[index] = inChar;
            index++;
            inData[index] = '\0';
        } else {
            index = 0;
            break;
        }
    }

    if (strcmp(inData, comp)  == 0) {
        for (int i=0; i<19; i++){
            inData[i]=0;
        }

        index = 0;
        serialFlush();
        return true;
    } else {
        return false;
    }
}

int16_t SerialCommunication::checkSetup() {

    if (Serial.available() > 0) {
        if (checkSerial("HHMESSAGESETUPID1\n")) {
            Serial.println("CMD SETUP1 RECEIVED");
            return 1;
        } else if (checkSerial("HHMESSAGESETUPID2\n")) {
            Serial.println("CMD SETUP2 RECEIVED");
            return 2;
        } else if (checkSerial("HHMESSAGESETUPID3\n")) {
            Serial.println("CMD SETUP3 RECEIVED");
            return 3;
        } else if (checkSerial("HHMESSAGESETUPID4\n")) {
            Serial.println("CMD SETUP4 RECEIVED");
            return 4;
        } else if (checkSerial("HHMESSAGESETUPID5\n")) {
            Serial.println("CMD SETUP5 RECEIVED");
            return 5;
        } else if (checkSerial("HHMESSAGESETUPID6\n")) {
            Serial.println("CMD SETUP6 RECEIVED");
            return 6;
        }
    }

    return -1;
}

void SerialCommunication::serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}

// JUST FOR DEBUGGING
int SerialCommunication::freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
// JUST FOR DEBUGGING
