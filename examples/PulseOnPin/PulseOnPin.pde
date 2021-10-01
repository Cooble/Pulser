#include "Pulser.h"
// if you want to change DUTY_PRECISION or PINS you need to modify Pulser.h
// see second example for notes

Pulser puls;

void setup() {
  //setting tone on default pin (PD2)=(digital pin 2 on arduino, 4th physical pin on AtMega328) with 1% on time (and 99% off time)
  puls.toone(60, 0.01f);//frequency = 60Hz, duty = 1%
  
  delay(5000);//wait for 5 sec
  
  puls.noToone();//switches off the tone (calls MACRO_PINOFF())
}

void loop() {
 //you can do normal stuff here
}


