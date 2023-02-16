#ifndef button_h
#define button_h
#include <Arduino.h>
class button {
   private:
    uint32_t _button;
    int _upState;           // the current reading from the input pin
    int lastUpState = LOW;  // the previous reading from the input pin

    unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
    unsigned long debounceDelay = 50;

   public:
    button(uint32_t buttonPin) { _button = buttonPin; }
    void begin() { pinMode(_button, INPUT); }
    bool up() {
        int reading = digitalRead(_button);
        if (reading != lastUpState) {
            lastDebounceTime = millis();
        }

        if ((millis() - lastDebounceTime) > debounceDelay) {
            if (reading != _upState) {
                _upState = reading;
            }
        }
        lastUpState = reading;
        return _upState;
    }
};

#endif  // button