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
// #include <U8g2lib.h>
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
//U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
DisplaySH1106_128x64_I2C display(-1);
//const char *text = "AZ-Delivery";
//u8g2_uint_t width;

#pragma region debug
void printSelectedDrinks()
{
    for (uint8_t i = 0; i < NUMPARTS; i++) {
        (selectedDrinks[i] == -1) ? Serial.println((String)i + ": NOT SET") : Serial.println((String)i + ": " + drinks[selectedDrinks[i]].name);
    }
}

void printArray(uint8_t array[], uint8_t size)
{
    for (uint8_t i = 0; i < size; i++) {
        Serial.println((String)i + ": " + array[i]);
    }
}
#pragma endregion

void setup()
{
    Serial.begin(9600);
    initAll();

    // int8_t *p = &selectedDrinks[0][0];
    // for (uint8_t i = 0; i < NUMPARTS; i++, p++)
    // {
    //     Serial.println(drinks[*p].name);
    //     p++;
    //     Serial.println(*p);
    // }
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
    // u8g2.begin();
    // u8g2.setFont(u8g2_font_logisoso32_tf);
    // width = u8g2.getUTF8Width(text);
    // u8g2.setFontMode(0);
    display.begin();
    display.setFixedFont(ssd1306xled_font6x8);

    display.fill( 0x00 );
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
    // for (int i = 0 ; i < 128 + width*3 ; i++ )
    // {
    //     u8g2.firstPage();
    //     u8g2.setFont(u8g2_font_logisoso32_tf);
    //     u8g2.drawUTF8(128 - i, 48, text);
    //     u8g2.nextPage();
    // }
    // u8g2.clearBuffer();
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

void loop()
{
    updateAll();

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
                    // Count parts
                }
            }
        }
    }
}
