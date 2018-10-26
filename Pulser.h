/**
   Uses timer1 to create PWM signal
   -> with variable duty cycle

   -> pin needs to be switched on/off in MACRO_PINON() and MACRO_PINOFF()
   It uses macros to achieve really fast switch instead of using extremely slow arduino method digitalWrite()

   -> output pin(s) must be set to OUTPUT with pinMode(pin)!
   This library doesn't modify pins at all. (Again because of slowness of arduino)

*/
#ifndef Pulser_h
#define Pulser_h
#include "Arduino.h"
#define CPU_FREQUENCY 16000000 //cpu freq in hertz

/**
  You can modify duty_precision from <2 to 255>
  when you need precision of 1/2 percent you can set it to 200
*/
#define DUTY_PRECISION 200 //you can set duty from 0=0% -> DUTY_PRECISION=100%

//defines max onTime in tenths of millis (10 means 1ms, 15 means 1.5ms)
//if duty is too high for the frequency, it will be changed to this max possible value
#define MAX_ON_TIME 10

//Edit this to change which pin(s) should be switched on
//this is called when pin should be switched on
#define MACRO_PINON() PORTD |= (1<<2)

//Edit this to change which pin(s) should be switched off
//It should switch off the pins which are switched on in MACRO_PINON()
#define MACRO_PINOFF() PORTD &= ~(1<<2)

//Edit this to be called when instance of pulser is created
//set pinMode(yourPin,OUTPUT) for your output pin
#define MACRO_PINMODE_INIT() DDRD |= (1<<2)

class Pulser
{
  public:
    Pulser();
    /**
       sets pulsing on pin specified by MACRO_PINON/OFF()
       freq in Hertz - from 1
       duty in interval (0; 1)
       if freq or duty == 0 -> noPulse() is called
    */
    void pulse(uint16_t freq, float duty);
    /**
       Disables pulsing.
    */
    void noPulse();
    
    static volatile uint8_t _dutySteps;
    static volatile uint8_t _maxDutySteps;
  private:
    void prescale(uint8_t p);
};
#endif
