#include "Timer.h"

volatile uint16_t millisecond = 0;
volatile uint16_t second = 0;

Timer::Timer(){
  TCNT2    = 0;
  TCCR2A  |= (1 << WGM21); // Configure timer 2 for CTC mode
  TCCR2B  |= (1 << CS22); // Start timer at Fcpu/64
  TIMSK2  |= (1 << OCIE2A); // Enable CTC interrupt
  OCR2A    = 250; // Set CTC compare value with a prescaler of 64

  // Activate Global Interrupts
  sei();
}

uint16_t Timer::millis(){
  return millisecond;
}

uint16_t Timer::seconds(){
  return second;
}

void Timer::delayMilliseconds(uint16_t ms)
{
	while (ms > 0) {
    ms--;
    _delay_loop_2(F_CPU/4000);
	}
}

void Timer::delayMicroseconds(uint16_t us){
    while(us--) {
      _delay_us(1);
    }
}

ISR (TIMER2_COMPA_vect)
{
  millisecond++;
  if(millisecond == 1000)
  {
    second++;
    millisecond = 0;
  }
}
