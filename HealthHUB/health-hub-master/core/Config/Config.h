/*
Author: David Bochan
Update: 7. Mai 2017
//--------------------------------------------------------------------------
*/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdint.h>

// Implements a interface for bidirectional serial communication
//
class Config
{
    const uint8_t SENSOR_HEART_RATE = 0;
    const uint8_t SENSOR_TEMP = 1;
    const uint8_t SENSOR_GSR = 2;
};

#endif // __SENSOR_H__
