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
// #include "Button.h"
// #include "SimpleTimer.h"
// #include "Pump.h"

// Config
const uint8_t buttonPins[] = {2, 3, 4, 5, 6, 7, 8};
const uint8_t pumpPins[] = {13, 12, 11, 10, 9};
// End Config

// Längen holen
const uint8_t numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]);
const uint8_t numPumps = sizeof(pumpPins) / sizeof(pumpPins[0]);

unsigned long counter = 0;
unsigned long i = 1;
uint8_t m = 1;
void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    TCCR2A = (1<<WGM21); // Wave Form Generation Mode 2: CTC
    TCCR2B = (1<<CS22) + (1<<CS21) + (1<<CS20) ; // prescaler = 1024
    TIMSK2 = (1<<OCIE2A); // interrupt when Compare Match with OCR2A
    OCR2A = 0xFF;
} 

void loop() {
    
}

ISR (TIMER2_COMPA_vect){  // Interrupt Service Routine 
    counter++;
    if (counter >= 61)
    {
        //Serial.println((String)i + ": " + millis() + " ms");
        //i++;
        digitalWrite(LED_BUILTIN, m);
        m++;
        if (m > 1) m = 0;
        counter = 0;
    }
}