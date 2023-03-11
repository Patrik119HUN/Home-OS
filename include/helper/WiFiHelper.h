#ifndef WiFiHelper_h
#define WiFiHelper_h
#include <Arduino.h>

#ifdef ARDUINO_SAM_DUE
#include <WiFiEspAT.h>
#elif STM32F0xx
#include <WiFiNINA.h>
#endif


void printMacAddress(byte mac[]);
const char* EncryptionType(int thisType);
void print2Digits(byte thisByte);
String mac2String(byte ar[]);
void listNetworks() {
    printf("** Scan Networks **\n");
    int numSsid = WiFi.scanNetworks();
    if (numSsid == -1) {
        Serial.println("Couldn't get a WiFi connection");
        while (true)
            ;
    }
    printf("Number of available networks: %d\n", numSsid);
    for (int thisNet = 0; thisNet < numSsid; thisNet++) {
        byte bssid[6];
        printf(
            "%d)\t[SSID]: %s\n\t[Signal]: %ld dBm\n\t[Channel]: %d\n\t[Encryption]: "
            "%s\n\t[BSSID]: ",
            thisNet + 1, WiFi.SSID(thisNet), WiFi.RSSI(thisNet), WiFi.channel(thisNet),
            EncryptionType(WiFi.encryptionType(thisNet))
        );
        Serial.print(mac2String(WiFi.BSSID(thisNet, bssid)));
        Serial.print("\n\n");
    }
}
const char* EncryptionType(int thisType) {
    switch (thisType) {
        case ENC_TYPE_WEP:
            return "WEP";
            break;
        case ENC_TYPE_TKIP:
            return "WPA";
            break;
        case ENC_TYPE_CCMP:
            return "WPA2";
            break;
        case ENC_TYPE_NONE:
            return "None";
            break;
        case ENC_TYPE_AUTO:
            return "Auto";
            break;
        case ENC_TYPE_UNKNOWN:
        default:
            return "Unknown";
            break;
    }
}
void print2Digits(byte thisByte) {
    if (thisByte < 0xF) {
        Serial.print("0");
    }
    Serial.print(thisByte, HEX);
}
String mac2String(byte ar[]) {
    String s;
    for (int i = 5; i >= 0; i--) {
        char buf[3];
        sprintf(
            buf, "%02X", ar[i]
        );  // J-M-L: slight modification, added the 0 in the format for padding
        s += buf;
        if (i > 0) s += ":";
    }
    return s;
}
#endif  // WiFi