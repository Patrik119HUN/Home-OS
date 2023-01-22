#ifndef Home_Assistant_h
#define Home_Assistant_h
#include <Arduino.h>

struct Home_Assistant {
    char name[256];
    uint32_t pin;
};

#endif  // Home_Assistant