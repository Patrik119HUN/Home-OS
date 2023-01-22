#ifndef Output_struct_h
#define Output_struct_h

#include <Arduino.h>
typedef struct {
    const uint32_t pin;
    boolean state;
    char name[256];
    void toggle() {
        digitalWrite(pin, state);
        state = !state;
    }
    void setName(const char* _name) { strcpy(name, _name); }
} Output;
Output _out[4] = {{46, LOW, "ceiling"}, {48, LOW, "fan"}, {50, LOW, "idk"}, {52, LOW, "asd"}};
#endif  // Output_struct