#ifndef sevseg_h
#define sevseg_h

#include <Arduino.h>
#define ARRAY_SIZE 8
class sevseg {
   private:
    uint32_t pins[ARRAY_SIZE];

   public:
    sevseg(
        uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t g,
        uint32_t dp
    ) {
        pins[0] = a;
        pins[1] = b;
        pins[2] = c;
        pins[3] = d;
        pins[4] = e;
        pins[5] = f;
        pins[6] = g;
        pins[7] = dp;
    }
    void init() {
        for (size_t i = 0; i < ARRAY_SIZE; i++) {
            pinMode(pins[i], OUTPUT);
        }
    }
    void clear() {
        for (size_t i = 0; i < ARRAY_SIZE; i++) {
            digitalWrite(pins[i], LOW);
        }
    };
    void print(byte in) {
        clear();
        for (size_t i = 0; i < ARRAY_SIZE; i++) {
            digitalWrite(pins[i], bitRead(in, i));
        }
    }
};
#endif  // sevseg