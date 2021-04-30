/*
Name: Sebastian Aigner
Datum: 2021-04-30 (yyyy-mm-dd)
Version: 1.0

Changelog:
1.0:
    Base version
*/


#ifndef _DRINK_H
#define _DRINK_H

#include "Arduino.h"

class Drink {
    String name;
    String acronym;
    uint8_t pumpid;
  
public:
    Drink() {};
    Drink(String name, String acronym, uint8_t pumpid);
};

#endif
