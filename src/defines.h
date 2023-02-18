#ifndef defines_h
#define defines_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LibPrintf.h>
#include <Scheduler.h>


#include "IO/Output/Binary.h"
#include "SevenSegment.h"
#include "Splash_Screen.h"
#include "helper/Log.h"
#include "interface/configuration.h"
#include "user_config.h"

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
uint8_t SD_PIN = 53;
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
#include <LiquidCrystalMenu.h>

#include "menu/mainMenu.h"
uint8_t LCD_COLS = 16;
uint8_t LCD_ROWS = 2;
LiquidCrystalMenu menu(LCD_ROWS, LCD_COLS, 36);
#endif

const uint8_t g = 37, f = 51, a = 49, b = 47, e = 45, d = 43, c = 41, dp = 39;
SevenSegment display(a, b, c, d, e, f, g, dp);
Logger _log;
#endif  // defines