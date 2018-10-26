#include "Pulser.h"
//if you want to change DUTY_PRECISION or PINS you need to modify Pulser.cpp

Pulser puls;
void setup() {
  //setting tone on default pin (PB1)=(digital pin 9) with 1% on time (and 99% off time)
  puls.toone(1, 0.01f);//frequency = 1Hz, duty = 1%
  delay(5000);//wait for 5 sec
  puls.noToone();//switches off the tone (automaticaly calls MACRO_PINOFF())
}

void loop() {
 //you can do normal stuff here
}


