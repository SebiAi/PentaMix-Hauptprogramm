/*
Name: Sebastian Aigner
Datum: 2021-01-30 (yyyy-mm-dd)
Version: 2.0

Changelog:
1.0:
  Base version
2.0:
  added ability to set pin to INPUT_PULLUP
*/


#ifndef _BUTTON_H
#define _BUTTON_H

#include "Arduino.h"
#include "SimpleTimer.h"

// Die vier Zustaende des Buttons
enum ButtonState {isPressed, bouncingOn, isReleased, bouncingOff};


class Button {
    byte pin;                           // der Arduino-Pin des Buttons
    bool isActiveHigh;                  // der Zustand des Buttons wenn er gedrueckt ist
    unsigned long debounceMS;           // Anzahl der Millisekunden bevor der Zustand
                                        //   gewaechselt wird (= Entprellzeit)
    SimpleTimer timer;                  // Timer, um die (stabile) Entprellzeit zu messen
    SimpleTimer longTimer;              // Timer, für hasLongClicked
    bool hasClicked = false;            // speichert einen Click bis zum naechsten
                                        //   Auslesen mit hasBtnClicked()
    bool hasLongClicked = false;        // speichert einen LongClick bis zum naechsten
                                        //   Auslesen mit hasBtnLongClicked()
    bool hasClickedAndReleased = false; // speichert einen Click und Release bis zum naechsten
                                        //   Auslesen mit hasBtnClickedAndReleased()
    ButtonState state;                  // der aktuelle Zustand des Buttons

  
public:
  Button(byte pin, bool isActiveHigh = true, unsigned long debounceMS = 10, bool pullup = false);
  Button() {};

  void update();

  bool isBtnPressed()  { return state == isPressed  || state == bouncingOn;  }
  bool isBtnReleased() { return state == isReleased || state == bouncingOff; }

  bool peekHasBtnClicked() { return hasClicked; }
  bool hasBtnClicked() { bool r = hasClicked;  hasClicked = false;  return r; }
  bool peekHasBtnLongClicked() { return hasLongClicked; }
  bool hasBtnLongClicked() { bool r = hasLongClicked; hasLongClicked = false; return r; }
  bool hasBtnClickedAndReleased() { bool r = hasClickedAndReleased; hasClickedAndReleased = false; return r; }
};

#endif
