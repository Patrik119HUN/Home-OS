#ifndef defines_h
#define defines_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LibPrintf.h>
#include <Scheduler.h>

#include "IO/Output/Binary.h"
#include "Splash_Screen.h"
#include "helper/Log.h"
#include "helper/button.h"
#include "interface/configuration.h"
#include "user_config.h"
#include "sevseg.h"

#ifdef WIFI_MODULE
#include <WiFiEspAT.h>
WiFiUDP wifi_udp;
#include "helper/WiFi.h"
#endif
#ifdef ETHERNET_MODULE
#include <Ethernet.h>
#include <SPI.h>
EthernetUDP ethernet_udp;
#endif
#ifdef SD_MODULE
uint8_t SD_PIN = 10;
#include <SD.h>
#include <SPI.h>
#endif
#ifdef RTC_MODULE
#include <RTClib.h>
#if defined WIFI_MODULE || ETHERNET_MODULE
#include <ArduinoHA.h>
#include <NTPClient.h>

#include "helper/NTP.h"
#ifdef WIFI_MODULE
NTPClient ntp(wifi_udp);
WiFiClient client;
HADevice device(mac, sizeof(mac));
HAMqtt mqtt(client, device);

// "myButtonA" and "myButtonB" are unique IDs of buttons. You should define you own ID.
HAButton buttonA("myButtonA");
HAButton buttonB("myButtonB");

#elif ETHERNET_MODULE
NTPClient ntp(ethernet_udp);
#else
NTPClient ntp();
#endif
#endif
RTC_DS3231 rtc;
#endif
#ifdef LCD_MODULE
#define USE_STANDARD_LCD
uint8_t LCD_COLS = 16;
uint8_t LCD_ROWS = 2;

const uint8_t rs = 12, rw = 13, en = 11, d0 = 9, d1 = 8, d2 = 7, d3 = 6, d4 = 5, d5 = 4, d6 = 3,d7 = 2;

int buttonVal[4];
uint32_t menuButtons[4] = {22, 24, 26, 28};
const long interval = 50;
unsigned long lastDebounceTime = 0;
unsigned long lcdTurnedOn = 0;
int lastVal[4] = {LOW};
int buttonState[4];

#include <LcdMenu.h>
#include <LiquidCrystal.h>
LcdMenu menu(LCD_ROWS, LCD_COLS);
#include "menu/mainMenu.h"

#define UP 56        // NUMPAD 8
#define DOWN 50      // NUMPAD 2
#define LEFT 52      // NUMPAD 4
#define RIGHT 54     // NUMPAD 6
#define ENTER 53     // NUMPAD 5
#define BACK 55      // NUMPAD 7
#define BACKSPACE 8  // BACKSPACE
#define CLEAR 46     // NUMPAD .
#endif

unsigned long previousMillis = 0;

const uint8_t g = 53,f = 51,a = 49,b = 47,e = 45,d = 43,c = 41,dp = 39;
sevseg display(a, b, c, d, e, f, g, dp);
Logger _log;
#endif //defines