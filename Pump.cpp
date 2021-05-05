#include "Pump.h"

Pump :: Pump(byte pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Pump :: dispense_ml(uint16_t milliliters)
{
    if (milliliters < 10) return;
    // Serial.println(milliliters/this->mlPerSecond*1000);
    timer.set(milliliters/this->mlPerSecond*1000);
    digitalWrite(pin, HIGH);
    isWorking = true;
}

uint64_t Pump :: getElapsedTime()
{
    return timer.get();
}

void Pump :: update()
{
    if (timer.elapsed() && timer.isInitialised)
    {
        digitalWrite(pin, LOW);
        isWorking = false;
    }
}
