#ifndef MQTTSettings_h
#define MQTTSettings_h

#include <Arduino.h>
#include <LcdMenu.h>
#include "../Settings.h"
extern MenuItem Settings[];
void inputCallback(String value);
MenuItem MQTTSetting[] = {
    ItemHeader(Settings),
    ItemInput("Host", inputCallback),
    ItemInput("Port", inputCallback),
    ItemFooter()
};

#endif  // MQTT