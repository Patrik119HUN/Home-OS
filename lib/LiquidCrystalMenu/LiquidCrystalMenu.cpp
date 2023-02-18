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

void LiquidCrystalMenu::menuLoop() {
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
    for (size_t i = 0; i < 4; i++) {
        _button[i].begin();
    }
    lcdTurnedOn = millis();
    setupLcdWithMenu(rs, rw, en, d0, d1, d2, d3, d4, d5, d6, d7, mainMenu);
}