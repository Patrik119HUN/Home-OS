#ifndef Output_struct_h
#define Output_struct_h

#include <Arduino.h>
#include <RTClib.h>
struct Output{
    const uint32_t pin;
    boolean state;
    const char* name;
    uint32_t lastUpadateTime;
    void toggle() {
        digitalWrite(pin, state);
        state = !state;
        lastUpadateTime = millis();
    }
    void setName(const char* _name) {
        name = _name;
    }
    
} ;
Output _out[4] = {{46, LOW, "ceiling"}, {48, LOW, "fan"}, {50, LOW, "idk"}, {52, LOW, "asd"}};
#endif  // Output_struct