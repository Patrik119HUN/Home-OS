#ifndef Network_h
#define Network_h

#include <Arduino.h>
#include <LcdMenu.h>
#include "../Settings.h"
extern MenuItem Settings[];
extern MenuItem WifiSettings[];
extern MenuItem EthSettings[];
extern MenuItem Network[];

MenuItem WifiSettings[] = {
    ItemHeader(Network),
    MenuItem("SSID:"),
    ItemFooter()
};

MenuItem EthSettings[] = {
    ItemHeader(Network),
    MenuItem("Ethernet setting"),
    ItemFooter()
};

MenuItem Network[] = {
    ItemHeader(Settings),
    ItemSubMenu("Wi-Fi", WifiSettings),
    ItemSubMenu("Ethernet", EthSettings),
    ItemFooter()
};
#endif  // Network