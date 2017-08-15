/*
Author: Eric Schmidt
Update: 24. April 2017
//--------------------------------------------------------------------------
*/

#ifndef __TIMER_H__
#define __TIMER_H__

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include "Singleton.h"

class Timer : public Singleton <Timer>
{
  friend class Singleton <Timer>;

  public:
    ~Timer () {}

    uint16_t millis();
    uint16_t seconds();

    void delayMilliseconds(uint16_t ms);
    void delayMicroseconds(uint16_t __us);

  protected:
    Timer ();
};

#endif // __TIMER_H__
