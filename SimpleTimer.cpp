#include "SimpleTimer.h"

SimpleTimer :: SimpleTimer() {
  running = false;
}

void SimpleTimer :: set(unsigned long duration) {
  startTime = millis();
  this->duration = duration;
  running = true;
  isInitialised = true;
}

uint64_t SimpleTimer :: get()
{
    return runTime - startTime;
}

bool SimpleTimer :: elapsed() {
  if (running) {
    if (millis() - startTime >= duration) {
      runTime = millis();
      running = false;
    }
  }
  return !running;
}
