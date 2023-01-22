#ifndef Settings_h
#define Settings_h

#include <Arduino.h>
#include <LcdMenu.h>
#include "Time/Time.h"
#include "Network/Network.h"
#include "MQTT/MQTTSettings.h"
#include "../mainMenu.h"
extern MenuItem mainMenu[];
MenuItem Settings[] = {
    ItemHeader(mainMenu),
    ItemSubMenu("Network", Network),
    ItemSubMenu("MQTT", MQTTSetting),
    ItemSubMenu("Time", Time),
    ItemFooter()
};
#endif  // Settings