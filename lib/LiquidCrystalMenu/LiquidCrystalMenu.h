#ifndef LIQUIDCRYSTALMENU_H
#define LIQUIDCRYSTALMENU_H

#include <Arduino.h>
#include <Button.h>
#include <Buzzer.h>
#include <LcdMenu.h>

#define _lcdBackLightPin 38
#define rs 12
#define rw 13
#define en 11
#define d0 9
#define d1 8
#define d2 7
#define d3 6
#define d4 5
#define d5 4
#define d6 3
#define d7 2

class LiquidCrystalMenu : LcdMenu, Buzzer {
   private:
    unsigned long lcdTurnedOn = 0;
    Button _button[4] = {Button(22), Button(24), Button(26), Button(28)};

    void navigate(int i);
    void turnOffBacklight(unsigned long time);

   public:
    LiquidCrystalMenu(uint8_t maxRows, uint8_t maxCols, uint32_t buzzerPin)
        : LcdMenu(maxRows, maxCols), Buzzer(buzzerPin) {}
    void begin(MenuItem* mainMenu);
    void loop();
};

#endif  // LIQUIDCRYSTALMENU_H
