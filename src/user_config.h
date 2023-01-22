#ifndef user_config_h
#define user_config_h

#include <Arduino.h>

unsigned long previousMillis = 0;
const long interval = 50;
#define CHARSET_SIZE 10
// Create your charset
char charset[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
// Active index of the charset
uint8_t charsetPosition;
uint32_t BAUD_RATE = 9600;
#ifdef LCD_MODULE
uint8_t LCD_COLS = 16;
uint8_t LCD_ROWS = 2;
uint32_t menuButtons[4] = {22, 24, 26, 28};
int buttonVal[4];
const uint8_t rs = 12, rw = 13, en = 11, d0 = 9, d1 = 8, d2 = 7, d3 = 6, d4 = 5, d5 = 4, d6 = 3,
              d7 = 2;
#endif
#ifdef SD_MODULE
uint8_t SD_PIN = 10;
#endif

#define UP 56        // NUMPAD 8
#define DOWN 50      // NUMPAD 2
#define LEFT 52      // NUMPAD 4
#define RIGHT 54     // NUMPAD 6
#define ENTER 53     // NUMPAD 5
#define BACK 55      // NUMPAD 7
#define BACKSPACE 8  // BACKSPACE
#define CLEAR 46     // NUMPAD .

namespace WiFi_Settings {
const char* ssid = "Wi-Fi";
const char* password = "Asdfghjkl12";
}  // namespace WiFi_Settings

namespace MQTT_Settings {
const char* ssid = "Wi-Fi";
const char* password = "Asdfghjkl12";
}  // namespace MQTT_Settings
#endif  // user_config