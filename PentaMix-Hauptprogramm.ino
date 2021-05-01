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
const uint8_t numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]);
const uint8_t numPumps = sizeof(pumpPins) / sizeof(pumpPins[0]);

// Arrays
Button buttons[numButtons];
Pump pumps[numPumps];
Drink drinks[numPumps];
int8_t selectedDrinks[NUMPARTS][2]; // { { drink array nummer, anzahl }, ... }

// Display
//U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
DisplaySH1106_128x64_I2C display(-1);
//const char *text = "AZ-Delivery";
//u8g2_uint_t width;

void setup()
{
    initAll();
    memset(selectedDrinks, -1, sizeof(selectedDrinks)); // TODO: [NOW] Set second part in two dimensional array to 0
}

#pragma region inits
void initAll()
{
    initButtons();
    initPumps();
    initDisplay();
    initDrinks();
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

void loop()
{
    updateAll();

    for (int i = 0; i < numButtons; i++)
    {
        if (buttons[i].hasBtnClicked())
        {
            if (i < 4) // Getränk Button
            {
                
            }

            if (i == 5) // Undo Button
            {
                
            }

            if (i == 6) // Ok Button
            {
                if (selectedDrinks[0][0] == -1)
                {
                    // Display error Message
                }
                else
                {
                    // Count parts
                }
            }
        }
    }
}
