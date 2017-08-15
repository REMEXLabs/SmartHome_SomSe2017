/*
Author: Nina Schaaf
Update: 10. June 2017
//--------------------------------------------------------------------------
*/

#ifndef __ADCHandler_H__
#define __ADCHandler_H__

#include <stdint.h>
#include <avr/io.h>

// Provides a class for initializing ADC and reading ADC Signals
class ADCHandler
{
  public:
    uint16_t ADC_Read(uint8_t pin);
    ADCHandler();
};

#endif // __ADCHandler_H__
