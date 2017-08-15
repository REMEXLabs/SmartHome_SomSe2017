/*
Author: Theresa Denhard
Update: 08. Juni 2017
//--------------------------------------------------------------------------
clock rate= 16MHz
Timer 0= 8-bit register (overflows after 255)
Timer period = 1/(16MHz)= 1,59*10^⁻5
ISR = 255* (1,59*10^-5)=0,0000159s --> 15 microseconds
therefore we need CTC (clear timer on compare match: line 27 to 30 and line 33) instead of line 32

*/
#include "TimerZero.h"

volatile uint16_t microsecond = 0;

TimerZero::TimerZero(){
  // initialize Timer0
  cli();             // disable global interrupts
  TCCR0A = 0;        // set entire TCCR0A register to 0
  TCCR0B = 0;        // set entire TCCR0A register to 0
  // set compare match register to desired timer count:
  //OCR0A = 15; //means: (1*10⁻6 (1 microsecond) / timer resolution)-1=15
  // turn on CTC mode:
  //TCCR0B |= (1 << WGM12);
  TCCR0B |= (1 << CS10); // Set CS10 bit so timer runs at clock speed, prescaler = 0
  TIMSK0 = (1 << TOIE0);//should be replaced through line 33
  //TIMSK0 = (1 << OCIE0A); // // enable Timer compare interrupt: trigger an interrupt when the timer overflows.
   // enable global interrupts:
   sei();
}

uint16_t TimerZero::micros(){
  return microsecond;
}
//interrupt service routine is called once the register overflows
ISR (TIMER0_OVF_vect){
  microsecond++; //increment microsecond after register overflow
}
