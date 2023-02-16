#ifndef BINARY_H
#define BINARY_H

#include <Arduino.h>
#include "interface/Home_Assistant/Output_struct.h"
class Binary {
   private:
    //Output _out[4] = {{46, LOW,"ceiling"}, {48, LOW,"fan"}, {50, LOW,"idk"}, {52, LOW,"asd"}};

   public:
    Binary() {
        for (size_t i = 0; i < 4; i++) {
            pinMode(_out[i].pin, OUTPUT);
        }
    }
    //Output& operator[](const uint8_t index) { return _out[index]; }

} _bin;

#endif  // BINARY_H
