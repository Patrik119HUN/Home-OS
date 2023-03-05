#include "LiquidCrystalMenu.h"

void LiquidCrystalMenu::navigate(int i) {
    if ((millis() - lcdTurnedOn) > 5 * 1000) return;
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

void LiquidCrystalMenu::turnOffBacklight(unsigned long time) {
    if ((millis() - lcdTurnedOn) > time) {
        digitalWrite(_lcdBackLightPin, LOW);
    }
}

void LiquidCrystalMenu::loop() {
    for (size_t i = 0; i < 4; i++) {
        if (_button[i].press() == HIGH) {
            digitalWrite(_lcdBackLightPin, HIGH);
            navigate(i);
            lcdTurnedOn = millis();
        }
    }
    turnOffBacklight(5000);
}

void LiquidCrystalMenu::begin(MenuItem* mainMenu) {
    Buzzer::begin();
    pinMode(_lcdBackLightPin, OUTPUT);
    for (size_t i = 0; i < 4; i++) {
        _button[i].begin();
    }
    lcdTurnedOn = millis();
    setupLcdWithMenu(_rs, _rw, _en, _d0, _d1, _d2, _d3, _d4, _d5, _d6, _d7, mainMenu);
}