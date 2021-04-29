#include "Button.h"

Button :: Button(byte pin, bool isActiveHigh, unsigned long debounceMS, bool pullup) {
  this->pin          = pin;
  this->isActiveHigh = isActiveHigh;
  this->debounceMS   = debounceMS;
  this->state        = isReleased;
  
  if (pullup) pinMode(pin, INPUT_PULLUP);
  else pinMode(pin, INPUT);
}

void Button :: update() {
  bool isButtonOn = (! isActiveHigh) ^ digitalRead(pin); // ^ = XOR
  
  switch (state) {
    case isReleased:
      if (isButtonOn) {
        state = bouncingOn;
        timer.set(debounceMS);
      }
      break;
      
    case bouncingOn:
      if (isButtonOn) {
        if (timer.elapsed()) {
          state = isPressed;
          hasClicked = true;
          longTimer.set(1000);
        }
      }
      else {
        timer.set(debounceMS);
      }
      break;
      
    case isPressed:
      if (longTimer.elapsed()) {
        hasLongClicked = true;
        longTimer.set(100);
      }
      if ( ! isButtonOn) {
        state = bouncingOff;
        timer.set(debounceMS);
      };
      
    case bouncingOff:
      if ( ! isButtonOn) {
        if (timer.elapsed()) {
          hasClickedAndReleased = true;
          state = isReleased;          
        }        
      }
      else {
        timer.set(debounceMS);
      }
      break;
  }
}
