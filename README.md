This library creates PWM signal of variable frequency and duty cycle.

# Pulser
- Uses timer1
- for Atmega328
- You can modify functions which are called to turn pin on/off by changing MACRO_PINON(), MACRO_PINOFF() in Pulser.h
- Useful for precise frequency and duty modulation.
- Great for driving Solid State Tesla Coils.

### How to use
First you need to set right pin(s) to be switched. To modify it replace code in macros MACRO_PINON(), MACRO_PINOFF(), MACRO_PINMODE_INIT(). It's truly recommended to use register access as it is the fastest.  
1. For example ```PORTD |= (1<<2)``` in MACRO_PINON() will set 3rd bit of port D to true.-> setting arduino pin 2 HIGH
2. Don't forget to change also MACRO_PINOFF() to ```PORTD &= ~(1<<2)```.  
3. Also you need to set pinMode(OUTPUT) for those pins. To do this simply replace code in MACRO_PINMODE_INIT(). ```DDRD |= (1<<2)```

![Alt text](YVOF3y5.jpg?raw=true "")

(And yes, that's Bill)
