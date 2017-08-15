/*
Author: Nina Schaaf
Update: 10. June 2017
//--------------------------------------------------------------------------
*/

#include "ADCHandler.h"

ADCHandler::ADCHandler()
{
  // Voltage reference selection for ADC
  ADMUX = (1<<REFS0); // AVCC with external capacitor at AREF pin

  // single conversion
  ADCSRA = (1 << ADPS2) | (1<<ADPS1) | (1<<ADPS0);  // Combination for division factor 128
  ADCSRA |= (1<<ADEN);                              // ADC enable

  ADCSRA |= (1<<ADSC);                              // ADC start conversion
  while (ADCSRA & (1<<ADSC) ) {                     // wait for completion of the conversion
  }
  (void) ADCW;
}

uint16_t ADCHandler::ADC_Read(uint8_t pin)
{
  //Select ADC Channel ch must be 0-7
  pin = pin&0b00000111;
  ADMUX |= pin;

  //Start Single conversion
  ADCSRA |= (1 << ADSC);

  //Wait for conversion to complete
  while(!(ADCSRA & (1 << ADIF)));

  //Clear ADIF by writing one to it
  ADCSRA |= (1 << ADIF);

  return(ADC);
}
