#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Button {
   private:
    uint32_t _buttonPin;
    int _buttonState;            // the current reading from the input pin
    int _lastButtonState = LOW;  // the previous reading from the input pin

    unsigned long lastDebounceTime = 0;   // the last time the output pin was toggled
    unsigned long _lastPressTime = 0;     // the last time the output pin was toggled
    unsigned long _pressTimeDelay = 200;  // the last time the output pin was toggled
    unsigned long _holdTimeDelay = 1000;  // the last time the output pin was toggled
    unsigned long debounceDelay = 50;

   public:
    Button(uint32_t buttonPin) : _buttonPin(buttonPin){};

    void begin() { pinMode(_buttonPin, INPUT); }

    bool state() {
        int reading = digitalRead(_buttonPin);
        if (reading != _lastButtonState) {
            lastDebounceTime = millis();
        }

        if ((millis() - lastDebounceTime) > debounceDelay) {
            if (reading != _buttonState) {
                _buttonState = reading;
            }
        }
        _lastButtonState = reading;
        return _buttonState;
    }
    bool press() {
        if (state() == HIGH && (millis() - _lastPressTime > _pressTimeDelay)) {
            _lastPressTime = millis();
            return HIGH;
        } else {
            return LOW;
        }
    }
};

#endif  // Button