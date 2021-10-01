#include "Pulser.h"

// Let's change PIN in Pulser.h let's say to pin 8 on Arduino
// using [manual](https://www.arduino.cc/en/Reference/PortManipulation) pin 8 is represented by zeroth bit of B register
//
// 1. set said pin to output using MACRO_PINMODE_INIT()
// such information is stored in DDRB in zeroth bit
// simply replace definition of MACRO_PINMODE_INIT() with 'DDRB |= (1<<0)' //zeroth bit
// this line is equivalent to (but hellishly faster than) 'pinMode(8,OUTPUT)'
//
// 2. change macro MACRO_PINON() which will be called to switch pin on
// this state is stored in register PORTB once again in the (lowest) zeroth bit
// replace definition of MACRO_PINON() with PORTB |= (1<<0) // set zeroth bit to one
// this line is equivalent to (but hellishly faster than) 'digitalWrite(8,ON)'
//
// 3. don't forget to change macro MACRO_PINOFF() which will be called to switch pin off
// this time we want to set said bit to zero:  PORTB &= ~(1<<0) //set zeroth bit to zero
// this line is equivalent to (but hellishly faster than) 'digitalWrite(8,OFF)'
//
// Finally the the changed section in Pulser.h will look like this:
//
//#define DUTY_PRECISION 200 
//#define MAX_ON_TIME 10
//#define MACRO_PINON() PORTB |= (1<<0)
//#define MACRO_PINOFF() PORTB &= ~(1<<0)
//#define MACRO_PINMODE_INIT() DDRB |= (1<<0)
//

// Note about MAX_ON_TIME: 
// When dealing with SSTCs it is very important not to leave coil on for two long without break,
// otherwise wonderful fumes of MOSFETs might join the party.
// To prevent that you can set maximum time for pin to be on using macro MAX_ON_TIME.
//
// This will override passed duty in case too high value is picked for the specified frequency
// by default, it is set to 10 meaning if duty is 0.5f for frequency 1Hz, duty would change to 0.001 (don't try)
// This would not work though since such low duty is not permitted by even the highest DUTY_PRECISION,
// minimal duty is equal to 1.f/DUTY_PRECISION.
// tl;dr if you need on-time higher than 1ms, increase MAX_ON_TIME


Pulser puls;

void setup() {
  //setting tone on default pin (PB0)=(digital pin 8 on arduino, 14th physical pin on AtMega328) with 1% on time (and 99% off time)
  puls.toone(314, 0.02f);//frequency = 314Hz, duty = 2% (on time will be 1/314*0.02)
  
  
}

int i = 0;
void loop() {
 //you can do normal stuff here
 while (i++ < 1000) {
	Serial.println("Doing something else and pwm is working");
 }
 puls.noToone();//switches off the tone (calls MACRO_PINOFF())
}


