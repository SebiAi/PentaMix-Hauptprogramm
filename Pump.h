/*
Name: Sebastian Aigner
Datum: 2021-04-30 (yyyy-mm-dd)
Version: 1.1

Changelog:
1.0:
    Base version
1.1:
    added getElapsedTime() function
*/


#ifndef _PUMP_H
#define _PUMP_H

#include "Arduino.h"
#include "SimpleTimer.h"

// Config
#define ML_PER_SECOND_DEFAULT 51
#define LEAD_TIME_MS 500
// End Config


class Pump {
    byte pin;
    uint8_t mlPerSecond = ML_PER_SECOND_DEFAULT;
    SimpleTimer timer;
  
public:
    bool isWorking = false;

    Pump() {};
    Pump(byte pin);

    void dispense_ml(uint16_t milliliters); // Gibt angegebene menge an Flüssigkeit aus.
    uint64_t getElapsedTime();              // Gibt die vom Timer tatsächliche verstrichene Zeit zurück

    void update();
};

#endif
