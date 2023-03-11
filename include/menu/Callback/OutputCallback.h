#ifndef OutputCallback_h
#define OutputCallback_h

#include <Arduino.h>

#include "../../interface/Home_Assistant/Output_struct.h"
#include "../mainMenu.h"

void outputCallback(uint8_t pin) {
    Serial.print(pin);
    _out[pin].toggle();
    if (_out[pin].state == HIGH) {
        mainMenu[2][pin + 1][2].setText("State:HIGH");
    } else {
        mainMenu[2][pin + 1][2].setText("State:LOW");
    }
}
#endif  // OutputCallback