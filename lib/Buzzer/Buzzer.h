#ifndef Buzzer_h
#define Buzzer_h

#include <Arduino.h>

class Buzzer {
   private:
    uint32_t _buzzerPin;

   public:
    Buzzer(uint32_t buzzerPin) { _buzzerPin = buzzerPin; }
    void begin() { pinMode(_buzzerPin, OUTPUT); }
    void beep(uint32_t beepLenght) {
        digitalWrite(_buzzerPin, HIGH);
        delay(beepLenght);
        digitalWrite(_buzzerPin, LOW);
    }
};

#endif  // Buzzer