#ifndef WIFI_h
#define WIFI_h
#include <Arduino.h>
#include <IPAddress.h>

struct Wifi {
    IPAddress WiFiIP;
    char ssid[64];
    char password[64];
};
#endif //WIFI