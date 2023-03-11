#ifndef DEFINES_H
#define DEFINES_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LibPrintf.h>

// #include <Scheduler.h>

#include "./pins/pins.h"
#include "SevenSegment.h"
#include "Splash_Screen.h"
#include "helper/Log.h"
#include "interface/configuration.h"
#include "user_config.h"

#ifdef WIFI_MODULE
#ifdef ARDUINO_SAM_DUE
#include <WiFiEspAT.h>
#elif STM32F0xx
#include "WiFiNINA.h"
#include "WiFiUdp.h"
#endif
WiFiUDP wifi_udp;
#include "helper/WiFiHelper.h"
#endif

#ifdef ETHERNET_MODULE
#include <Ethernet.h>
#include <SPI.h>
EthernetUDP ethernet_udp;
#endif

#ifdef SD_MODULE
#include <SD.h>
#include <SPI.h>
#endif

#ifdef RTC_MODULE
#include "interface/Time/TimeWrapper.h"
#endif

#if defined WIFI_MODULE || ETHERNET_MODULE
#include <ArduinoHA.h>
#include <NTPClient.h>

#include "helper/NTP.h"
#ifdef WIFI_MODULE
NTPClient ntp(wifi_udp);
WiFiSSLClient client;
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

TimeWrapper rtc;

#ifdef LCD_MODULE
#include <LiquidCrystalMenu.h>

#include "menu/mainMenu.h"
LiquidCrystalMenu menu(LCD_ROWS, LCD_COLS, BuzzerPin);
#endif

#ifdef SEVSEG_MODULE
SevenSegment display(a, b, c, d, e, f, g, dp);
#endif
Logger _log;

#endif  // DEFINES_H
