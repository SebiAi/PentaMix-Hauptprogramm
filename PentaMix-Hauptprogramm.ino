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
#include <U8g2lib.h>
#include "Button.h"
#include "SimpleTimer.h"

// Config
const uint8_t buttonPins[] = {2, 3, 4, 5, 6, 7, 8};
const uint8_t pumpPins[] = {13, 12, 11, 10, 9};
// End Config

// Längen holen
const uint8_t numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]);
const uint8_t numPumps = sizeof(pumpPins) / sizeof(pumpPins[0]);

// Display
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(){

} 

void loop() {
    
}