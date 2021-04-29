/*
Name: Sebastian Aigner
Datum: 2021-04-10 (yyyy-mm-dd)
Version: 1.0
Beschreibung: Hauptprogramm des PentaMix Projekts. Liest Knöpfe ein und steuert die Pumpen

Changelog:
1.0:
    Base version
*/

#include "Arduino.h"
#include <Servo.h>
#include "Button.h"
#include "SimpleTimer.h"
// #include "Pump.h"

// Config
const uint8_t buttonPins[] = {2, 3, 4, 5, 6, 7, 8};
const uint8_t pumpPins[] = {13, 12, 11, 10, 9};
// End Config

// Längen holen
const uint8_t numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]);
const uint8_t numPumps = sizeof(pumpPins) / sizeof(pumpPins[0]);

void setup(){

} 

void loop() {
    
}