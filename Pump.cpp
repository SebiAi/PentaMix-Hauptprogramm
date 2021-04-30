#include "Pump.h"

Pump :: Pump(byte pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Pump :: dispense_ml(uint16_t milliliters)
{
    if (milliliters < 10) return;
    timer.set(milliliters/this->mlPerSecond*1000);
    digitalWrite(pin, HIGH);
}

void Pump :: update()
{
    if (timer.elapsed() && timer.isInitialised)
    {
        digitalWrite(pin, LOW);
    }
}