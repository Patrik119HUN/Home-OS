#ifndef MQTT_h
#define MQTT_h

#include <Arduino.h>
#include <IPAddress.h>

struct MQTT {
    char server[256];
    char username[256];
    char password[256];
    char id[256];
    uint16_t port;
    uint16_t SocketTimeout;
    uint16_t KeepAlive;
    uint16_t BufferSize;
};

#endif  // MQTT