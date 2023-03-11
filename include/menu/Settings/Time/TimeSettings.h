#ifndef TimeSettings_h
#define TimeSettings_h

#include <Arduino.h>
#include <LcdMenu.h>
#include "../Settings.h"
extern MenuItem Settings[];
MenuItem Time[] = {
    ItemHeader(Settings),
    MenuItem("TimeZones:"),
    ItemFooter()
};
#endif  // Time