/*
Name: Sebastian Aigner
Datum: 2021-02-24 (yyyy-mm-dd)
Version: 2.1

Changelog:
1.0:
    Base version
2.0:
    isInitialised variable added that gets set to true uppon first set()
2.1:
    added get() function
*/


#ifndef _SIMPLETIMER_H
#define _SIMPLETIMER_H

#include "Arduino.h"

class SimpleTimer {
    unsigned long startTime;
    unsigned long duration;
    unsigned long runTime;
    bool running;
  
public:
    bool isInitialised = false;
    SimpleTimer();
    void set(unsigned long duration);
    uint64_t get();
    bool elapsed();
};

#endif
