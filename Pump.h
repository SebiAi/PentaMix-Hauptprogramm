/*
Name: Sebastian Aigner
Datum: 2021-04-30 (yyyy-mm-dd)
Version: 1.0

Changelog:
1.0:
    Base version
*/


#ifndef _PUMP_H
#define _PUMP_H

#include "Arduino.h"
#include "SimpleTimer.h"

class Pump {
    byte pin;
    SimpleTimer timer;
  
public:
    Pump() {};
    Pump(byte pin);

    void update();

};

#endif
