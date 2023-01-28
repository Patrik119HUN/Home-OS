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
#include <SD.h>
#include <SPI.h>
#endif
#ifdef RTC_MODULE
#include <RTClib.h>
#if defined WIFI_MODULE || ETHERNET_MODULE
#include <NTPClient.h>

#include "helper/NTP.h"
#ifdef WIFI_MODULE
NTPClient ntp(wifi_udp);
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
#include <LcdMenu.h>
#include <LiquidCrystal.h>
LcdMenu menu(LCD_ROWS, LCD_COLS);
#include "menu/MainMenu.h"
#endif
Logger _log;

unsigned long lastDebounceTime = 0;
int lastVal[4] = {LOW};
int buttonState[4];
void setup() {
    Serial.begin(BAUD_RATE);
    for (size_t i = 0; i < 9; i++) {
        Serial.println(Splash_screen[i]);
    }
    printf("\nVersion:\n\t %s\n", VERSION);
    printf("Built On:\n \t[Date]: %s\n\t[Time]: %s\n", __DATE__, __TIME__);
    printf("Made by:\n\tTukacs Patrik\n");

#ifdef WIFI_MODULE
    Serial1.begin(115200);
WIFI_BEGIN:
    WiFi.init(Serial1);
    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println(F("Communication with WiFi module failed!"));
        Serial.println(F("Retrying WIFI initializaton!"));
        delay(1000);
        goto WIFI_BEGIN;
    }
    byte mac[6];
    WiFi.macAddress(mac);
    printf("[Wi-Fi MAC]: \n\t");
    Serial.print(mac2String(mac));
    Serial.println();
    Serial.println("Scanning available networks...");
    listNetworks();
    if (WiFi.begin("Wi-Fi", "Asdfghjkl12") == WL_CONNECTED) {
        printf(
            "\nSuccesfully connected to:\n\t[SSID]:%s\n\t[Password]:%s\n", "Wi-Fi", "Asdfghjkl12"
        );
    }
#endif
#ifdef SD_MODULE
SD_BEGIN:
    if (!SD.begin(SD_PIN)) {
        Serial.println(F("Failed to initialize SD library"));
        Serial.println(F("Retrying SD initializaton!"));
        delay(1000);
        goto SD_BEGIN;
    }
    conf.begin();
    conf.loadMQTT();
    conf.loadWIFI();
#endif
#ifdef RTC_MODULE
RTC_BEGIN:
    if (!rtc.begin()) {
        Serial.println(F("Failed to initialize RTC library"));
        Serial.println(F("Retrying RTC initializaton!"));
        delay(1000);
        goto RTC_BEGIN;
        // ntp.begin();
    }

#endif
#ifdef LCD_MODULE
    
    menu.setupLcdWithMenu(rs, rw, en, d0, d1, d2, d3, d4, d5, d6, d7, mainMenu);
    for (size_t i = 0; i < 4; i++) {
        pinMode(menuButtons[i], INPUT);
    }
#endif
    charsetPosition = 0;

}
void loop() {
    // UpdateNTP(wifi_udp, &ntp, &rtc);

    // ntp.update();
    // DateTime time = rtc.now();
    //_log.println("hello", ACK);
    //   if (WiFi.begin("Wi-Fi", "Asdfghjkl12") == WL_CONNECTED) {
    //      printf(
    //          "\nSuccesfully connected to:\n\t[SSID]:%s\n\t[Password]:%s\n", "Wi-Fi",
    //          "Asdfghjkl12"
    //      );
    //  }
    for (size_t i = 0; i < 4; i++) {
        buttonVal[i] = digitalRead(menuButtons[i]);
        if (buttonVal[i] != lastVal[i]) {
            lastDebounceTime = millis();
        }
    }

    if ((millis() - lastDebounceTime) > interval) {
        for (size_t i = 0; i < 4; i++) {
            if (buttonVal[i] != buttonState[i]) {
                buttonState[i] = buttonVal[i];
                if (buttonState[i] == HIGH) {
                    switch (i) {
                        case 0:
                            menu.up();
                            break;
                        case 1:
                            menu.down();
                            break;
                        case 2:
                            menu.enter();
                            break;
                        case 3:
                            menu.back();
                            break;
                    }
                }
            }
        }
    }
    char command = Serial.read();

    switch (command) {
        case UP:
            if (menu.isInEditMode())  // Update the position only in edit mode
                charsetPosition = (charsetPosition + 1) % CHARSET_SIZE;
            menu.drawChar(charset[charsetPosition]);  // Works only in edit mode
            menu.up();
            break;
        case DOWN:
            if (menu.isInEditMode())  // Update the position only in edit mode
                charsetPosition = constrain(charsetPosition - 1, 0, CHARSET_SIZE);
            menu.drawChar(charset[charsetPosition]);  // Works only in edit mode
            menu.down();
            break;
        case LEFT:
            menu.left();
            break;
        case RIGHT:
            menu.right();
            break;
        case ENTER:                               // Press enter to go to edit mode : for ItemInput
            menu.type(charset[charsetPosition]);  // Works only in edit mode
            menu.enter();
            break;
        case BACK:
            menu.back();
            break;
        case CLEAR:
            menu.clear();
            break;
        case BACKSPACE:  // Remove one character from tail
            menu.backspace();
            break;
        default:
            break;
    }
    for (size_t i = 0; i < 4; i++) {
        lastVal[i] = buttonVal[i];
    }
    
}