/*
Author: Theresa Denhard
Update: 08. Juni 2017
//--------------------------------------------------------------------------
*/

#ifndef __TIMERZERO_H__
#define __TIMERZERO_H__

#include <avr/interrupt.h>
#include <avr/io.h>
#include "Singleton.h"

class TimerZero : public Singleton <TimerZero>
{
  friend class Singleton <TimerZero>;

  public:
    ~TimerZero () {}

    uint16_t micros();

  protected:
    TimerZero();
};

#endif // __TIMERZERO_H__
