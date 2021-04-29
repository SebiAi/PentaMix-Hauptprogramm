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

bool SimpleTimer :: elapsed() {
  if (running) {
    if (millis() - startTime >= duration) {
      running = false;
    }
  }
  return !running;
}
