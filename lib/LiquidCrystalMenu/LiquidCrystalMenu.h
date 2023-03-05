#ifndef LIQUIDCRYSTALMENU_H
#define LIQUIDCRYSTALMENU_H

#include <Arduino.h>
#include <Button.h>
#include <Buzzer.h>
#include <LcdMenu.h>

class LiquidCrystalMenu : LcdMenu, Buzzer {
   private:
    uint8_t _rs,_rw,_en,_d0,_d1,_d2,_d3,_d4,_d5,_d6,_d7,_lcdBackLightPin;
    uint32_t lcdTurnedOn = 0;
    Button _button[4] = {Button(22), Button(24), Button(26), Button(28)};

    void navigate(int i);
    void turnOffBacklight(unsigned long time);

   public:
    LiquidCrystalMenu(uint8_t maxRows, uint8_t maxCols, uint32_t buzzerPin)
        : LcdMenu(maxRows, maxCols), Buzzer(buzzerPin) {}
    void setLCDPins(
        uint8_t rs, uint8_t rw, uint8_t en, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
        uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,uint8_t _lcdBackLightPin
    );
    void begin(MenuItem* mainMenu);
    void loop();
};

#endif  // LIQUIDCRYSTALMENU_H
