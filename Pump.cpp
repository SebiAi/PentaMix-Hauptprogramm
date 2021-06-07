#include "Pump.h"

Pump :: Pump(byte pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Pump :: dispense_ml(uint16_t milliliters)
{
    if (milliliters < 10) return;
    timer.set((double)milliliters/this->mlPerSecond*1000 + LEAD_TIME_MS);
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
