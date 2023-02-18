#ifndef LiquidCrystalMenu_h
#define LiquidCrystalMenu_h

#include <Arduino.h>
#include <Button.h>
#include <Buzzer.h>
#include <LcdMenu.h>
class LiquidCrystalMenu : LcdMenu, Buzzer {
   private:
    const uint32_t _lcdBackLightPin = 38;
    const uint8_t rs = 12, rw = 13, en = 11, d0 = 9, d1 = 8, d2 = 7, d3 = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
    unsigned long lcdTurnedOn = 0;
    Button _button[4] = {Button(22), Button(24), Button(26), Button(28)};

   public:
    LiquidCrystalMenu(uint8_t maxRows, uint8_t maxCols,uint32_t buzzerPin) : LcdMenu(maxRows, maxCols),Buzzer(buzzerPin){}

    void begin(MenuItem* mainMenu) {
        Buzzer::begin();
        for (size_t i = 0; i < 4; i++) {
            _button[i].begin();
        }
        lcdTurnedOn = millis();
        setupLcdWithMenu(rs, rw, en, d0, d1, d2, d3, d4, d5, d6, d7, mainMenu);
    }

    void menuLoop() {
        digitalWrite(_lcdBackLightPin, HIGH);
        for (size_t i = 0; i < 4; i++) {
            if (_button[i].press() == HIGH && ((millis() - lcdTurnedOn) < 5 * 1000)) {
                switch (i) {
                    case 0:
                        up();
                        break;
                    case 1:
                        down();
                        break;
                    case 2:
                        enter();
                        break;
                    case 3:
                        back();
                        break;
                }
                beep(100);
            }
            lcdTurnedOn = millis();
        }
        turnOffBacklight(5000);
    }
    void turnOffBacklight(unsigned long time) {
        if ((millis() - lcdTurnedOn) > time) {
            digitalWrite(_lcdBackLightPin, LOW);
        }
    }
};

#endif LiquidCrystalMenu