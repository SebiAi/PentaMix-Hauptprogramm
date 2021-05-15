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
#include <lcdgfx.h>
#include <lcdgfx_gui.h>
#include "Button.h"
#include "SimpleTimer.h"
#include "Pump.h"
#include "Drink.h"
#include "defines.h"

// Config
#define NUMDRINKS 5
#define CUPSIZEML 330                                       // Bechergröße in ml
#define NUMPARTS 10                                         // Anzahl an verschiedenen Anteilen
const uint8_t buttonPins[] = {2, 3, 4, 5, 6, 7, 8};         // 0 bis 4 - Getränk 1 bis 5, 5 - Undo, 6 Ok
const uint8_t pumpPins[NUMDRINKS] = {13, 12, 11, 10, 9};    // 0 bis 4 - Getränk 1 bis 5
// End Config

// Längen holen
const uint8_t numButtons = GETARRAYLENGTH(buttonPins);
const uint8_t numPumps = GETARRAYLENGTH(pumpPins);

// Arrays
Button buttons[numButtons];
Pump pumps[numPumps];
Drink drinks[numPumps];
int8_t selectedDrinks[NUMPARTS];

// Display
DisplaySH1106_128x64_I2C display(-1);

#pragma region debug
void printSelectedDrinks()
{
    for (uint8_t i = 0; i < NUMPARTS; i++) {
        (selectedDrinks[i] == -1) ? Serial.println((String)i + ": NOT SET") : Serial.println((String)i + ": " + drinks[selectedDrinks[i]].name);
    }
}

void printArray(uint16_t *array, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++, array++) {
        Serial.println((String)i + ": " + *array);
    }
}
#pragma endregion

void setup()
{
    Serial.begin(9600);
    initAll();
    printSelectedDrinks();
}

#pragma region inits
void initAll()
{
    initButtons();
    initPumps();
    initDisplay();
    initDrinks();
    initSelectedDrinks();
}

void initButtons()
{
    for (int8_t i = 0; i < numButtons; i++)
    {
        buttons[i] = Button(buttonPins[i], false, 10, true); // active LOW, 10 ms debounce time, activate pullup
    }
}

void initPumps()
{
    for (int8_t i = 0; i < numPumps; i++)
    {
        pumps[i] = Pump(pumpPins[i]);
    }
}

void initDisplay()
{
    display.begin();
    display.setFixedFont(ssd1306xled_font6x8);
    display.fill( 0x00 );

    display.swapDimensions();

    display.write("Hello World!");
}

void initDrinks()
{
    for (int8_t i = 0; i < numPumps; i++)
    {
        drinks[i] = Drink((String)"Drink " + (i + 1), (String)"D" + (i + 1), i);
    }
}

void initSelectedDrinks()
{
    // uint8_t u = 0;
    // for (uint8_t i = 0; i < NUMPARTS * 2; i++)
    // {
    //     selectedDrinks[i - i % 2 - u][i % 2] = -1 + i % 2;
    //     u += i % 2;
    // }
    memset(selectedDrinks, -1, sizeof(selectedDrinks));
}
#pragma endregion

#pragma region updates
void updateAll()
{
    updateButtons();
    updatePumps();
    updateDisplay();
}

void updateButtons()
{
    for (int8_t i = 0; i < numButtons; i++)
    {
        buttons[i].update();
    }
}

void updatePumps()
{
    for (int8_t i = 0; i < numPumps; i++)
    {
        pumps[i].update();
    }
}

void updateDisplay()
{
    // TODO: Test Display & write function
}
#pragma endregion

#pragma region part functions
void addPart(uint8_t i)
{
    uint8_t partnr = 0;
    
    for (; partnr < NUMPARTS; partnr++)
    {
        // Find empty part slot
        if (selectedDrinks[partnr] == -1)
        {
            // add part
            selectedDrinks[partnr] = i;
            Serial.println((String)"Set part " + partnr + " to " + i);
            break;
        }
    }
    if (partnr == NUMPARTS)
    {
        // Display error Message (already 10 parts)
        Serial.println("[ERROR] ALL PARTS FULL");
        // TODO: Also on Display
    }
    printSelectedDrinks();
}

void undoPart(uint8_t i)
{
    int8_t partnr = NUMPARTS - 1;
    
    for (; partnr >= 0; partnr--)
    {
        // Find last added part
        if (selectedDrinks[partnr] != -1)
        {
            // Remove part
            selectedDrinks[partnr] = -1;
            Serial.println((String)"Set part " + partnr + " to NOT SET");
            break;
        }
    }
    printSelectedDrinks();
}
#pragma endregion

#pragma region help functions
void calculateMls(uint16_t *partsSum, uint8_t size, uint8_t sumParts, uint16_t cupSizeMl)
{
    uint8_t partnr = 0;
    for (; partnr < size; partnr++, partsSum++)
    {
        *partsSum = cupSizeMl / sumParts * (*partsSum);
    }    
}
#pragma endregion

void loop()
{
    updateAll(); // TODO: Mabe optimise => one for loop with all updates

    for (uint8_t i = 0; i < numButtons; i++)
    {
        if (buttons[i].hasBtnClicked())
        {
            Serial.println((String)"Button " + i);
            if (i < 4) // Getränk Button
            {
                addPart(i);
            }

            if (i == 5) // Undo Button
            {
                undoPart(i);
            }

            if (i == 6) // Ok Button
            {
                if (selectedDrinks[0] == -1)
                {
                    // Display error Message (no parts)
                    Serial.println("[ERROR] NO PARTS");
                    // TODO: Also on Display
                }
                else
                {
                    // count parts
                    uint16_t partsSum[numPumps];
                    memset(partsSum, 0, sizeof(partsSum));

                    uint8_t partnr = 0;
                    uint8_t sumParts = 0;
                    for (; partnr < NUMPARTS; partnr++)
                    {
                        if (selectedDrinks[partnr] != -1)
                        {
                            partsSum[selectedDrinks[partnr]]++;
                            sumParts++;
                        }
                    }
                    Serial.println("<Counted Parts>");
                    printArray(partsSum, GETARRAYLENGTH(partsSum));
                    Serial.println("</Counted Parts>");

                    // calulate ml
                    Serial.println("<calulate ml>");
                    calculateMls(partsSum, GETARRAYLENGTH(partsSum), sumParts, CUPSIZEML);
                    printArray(partsSum, GETARRAYLENGTH(partsSum));
                    Serial.println("</calulate ml>");

                    // operate Pumps
                    Serial.println("<operate Pumps>");
                    partnr = 0;
                    for (; partnr < GETARRAYLENGTH(partsSum); partnr++)
                    {
                        pumps[partnr].dispense_ml(partsSum[partnr]);
                    }

                    uint8_t numPumpsWorking = numPumps;
                    // TODO: Display that pumps are working
                    while (numPumpsWorking > 0)
                    {
                        numPumpsWorking = 0;
                        partnr = 0;                        
                        for (; partnr < GETARRAYLENGTH(partsSum); partnr++)
                        {
                            pumps[partnr].update();
                            if (pumps[partnr].isWorking) numPumpsWorking++;                            
                        }
                    }
                    Serial.println("</operate Pumps>");
                    for (uint8_t debug = 0; debug < GETARRAYLENGTH(partsSum); debug++)
                    {
                        Serial.println((unsigned long)pumps[debug].getElapsedTime());
                    }

                    // TODO: clear selectedDrinks and refresh display
                }
            }
        }
    }
}
