#include "Arduino.h"
#include "Pulser.h"

volatile uint8_t Pulser::_dutySteps;
volatile uint8_t Pulser::_maxDutySteps;

Pulser::Pulser() {
    MACRO_PINMODE_INIT();
    MACRO_PINOFF();
}
/**
   sets prescale for timer 0
   0 - no prescale = 1
   1 - 8
   2 - 64
   3 -256
   4 - 1024
*/
void Pulser::prescale(uint8_t p) {
  TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
  switch (p) {
    case 0:
      TCCR1B |= (1 << CS10);
      break;
    case 1:
      TCCR1B |= (1 << CS11);
      break;
    case 2:
      TCCR1B |= (1 << CS11) | (1 << CS10);
      break;
    case 3:
      TCCR1B |= (1 << CS12);
      break;
    case 4:
      TCCR1B |= (1 << CS12) | (1 << CS10);
      break;
  }
}
/**
   freq in hertz, duty cycle between 0 to 1
   if duty or freq = 0 -> noPulse() is called
*/
void Pulser::pulse(uint16_t freq, float duty) {
  if(duty == 0 | freq == 0){
     noPulse();
     return;
  }
  cli();  // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  Pulser::_dutySteps = 0;
  Pulser::_maxDutySteps = (duty * DUTY_PRECISION);

  //eats around 4 us of time
  uint16_t onTime = (uint16_t)( 10000.0 / DUTY_PRECISION / freq * Pulser::_maxDutySteps); //on time in tenths of ms
  if (onTime > MAX_ON_TIME)//this checks if ontime is above limit and if true -> it modifies steps to achieve the max possible duty for this frequency
    Pulser::_maxDutySteps = (uint8_t)(MAX_ON_TIME / 10000.0 * DUTY_PRECISION * freq);

  uint32_t cr = (uint32_t)((CPU_FREQUENCY / DUTY_PRECISION) / freq);//this value needs to be divided by prescaller to get Compare Register Value
  uint32_t crv = cr;
  uint8_t prescal = 0;
  if (crv > 0xFFFE) {
    crv = cr / 8;
    prescal = 1;
    if (crv > 0xFFFE) {
      crv = cr / 64;
      prescal = 2;
      if (crv > 0xFFFE) {
        crv = cr / 256;
        prescal = 3;
        if (crv > 0xFFFE) {
          crv = cr / 1024;
          prescal = 4;
        }
      }
    }
  }
  OCR1A = crv;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  prescale(prescal);
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  sei();             // enable all interrupts
}
void Pulser::noPulse() {
  cli();
  TCCR1A = 1;
  TCCR1B = 3;
  OCR1A = 0;
  TIMSK1 = 0;
  MACRO_PINOFF();
  sei();
}
ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  if (Pulser::_dutySteps == 0){
    MACRO_PINON();
    }
  else if (Pulser::_dutySteps == Pulser::_maxDutySteps){
    MACRO_PINOFF();
  }
  Pulser::_dutySteps++;
 // if (Pulser::_dutySteps == DUTY_PRECISION)
  Pulser::_dutySteps %= DUTY_PRECISION;
}



