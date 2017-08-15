/*
Author: David Bochan
Update: 7. Mai 2017
//--------------------------------------------------------------------------
*/

#ifndef __SERIAL_COMMUNICATION_H__
#define __SERIAL_COMMUNICATION_H__

#include <stdint.h>
#include <string.h>
#include <Arduino.h>
#include "Singleton.h"

// Implements a interface for bidirectional serial communication
//
class SerialCommunication : public Singleton <SerialCommunication>
{
  friend class Singleton <SerialCommunication>;

  public:
    ~SerialCommunication () {}

    bool sendData(int16_t id, int16_t heartrate, int16_t temp, int16_t gsr);
    bool sendStream(int16_t sensor, int16_t signal);
    bool setError(int16_t sensor);
    bool setState(uint8_t state);
    bool setup();
    void readSerial();
    bool checkSerial(char* comp);
    int16_t checkSetup();
    int freeRam();

  protected:
    SerialCommunication() {}

  private:
    const char *START;
    const char *MSG;
    void serialFlush();

    uint8_t append(char* s, size_t size, char c);
};


#endif // __SENSOR_H__
