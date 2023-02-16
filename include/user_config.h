#ifndef user_config_h
#define user_config_h

#include <Arduino.h>

byte mac[] = {0x00, 0x10, 0xFA, 0x6E, 0x38, 0x4A};
uint32_t BAUD_RATE = 9600;

namespace WiFi_Settings {
const char* ssid = "Wi-Fi";
const char* password = "Asdfghjkl12";
}  // namespace WiFi_Settings

namespace MQTT_Settings {
const char* ssid = "Wi-Fi";
const char* password = "Asdfghjkl12";
}  // namespace MQTT_Settings
#endif  // user_config