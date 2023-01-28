#ifndef mainMenu_h
#define mainMenu_h
#include <Arduino.h>
#include <LcdMenu.h>
#include <generatemenu.h>

#include "Outputs/Outputs.h"
#include "Settings/Settings.h"

void inputCallback(String value);
MenuItem mainMenu[] = {
    ItemHeader(),
    ItemSubMenu("Settings", Settings),
    ItemSubMenu("Outputs", mainMenu),
    ItemInput("wifi", "Wi-Fi", inputCallback),
    ItemFooter()};
void inputCallback(String value) {
    Serial.print(F("# "));
    Serial.println(value);
}

#endif  // MainMenu