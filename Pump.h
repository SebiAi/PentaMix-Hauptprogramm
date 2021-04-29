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

// Config
#define ML_PER_SECOND_DEFAULT 20
// End Config


class Pump {
    byte pin;
    uint8_t mlPerSecond = ML_PER_SECOND_DEFAULT;
    SimpleTimer timer;
  
public:
    Pump() {};
    Pump(byte pin);

    void dispense_ml(uint16_t milliliters); // Gibt angegebene menge an Flüssigkeit aus.

    void update();
};

#endif
