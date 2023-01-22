#ifndef configuration_h
#define configuration_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SD.h>

#include "../user_config.h"
#include "Home_Assistant/Home_Assistant.h"
#include "MQTT/MQTT.h"
#include "network/Ethernet.h"
#include "network/WIFI.h"
#include "../interface/Home_Assistant/Output_struct.h"
class Configuration {
   private:
    File _file;
    char _filename[256];
    StaticJsonDocument<1024> _doc;
    DeserializationError _error;

   public:
    char hostname[64];
    char time_zone[9];
    Wifi _wifi;
    MQTT _mqtt;
    Home_Assistant* _ha;
    Configuration(const char* filename) { strcpy(_filename, filename); }
    void begin() {
        _file = SD.open(_filename);
        _error = deserializeJson(_doc, _file);
        if (_error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(_error.c_str());
        }
        _file.close();
    }
    void loadMQTT() {
        JsonObject mqtt = _doc["mqtt"];
        strcpy(_mqtt.server, mqtt["server"]);
        strcpy(_mqtt.password, mqtt["password"]);
        strcpy(_mqtt.username, mqtt["username"]);
        strcpy(_mqtt.id, mqtt["id"]);
        _mqtt.port = mqtt["port"];
        JsonArray ha = mqtt["Home_assistant"];

        //_ha = (Home_Assistant*)malloc(ha.size() * sizeof(Home_Assistant));
        for (size_t i = 0; i < ha.size(); i++) {
          //   strcpy(_ha[i].name, ha[i]["name"]);
             //_out[i].setName(ha[i]["name"]);
            //_ha[i].pin = ha[i]["type"];
        }
    }
    void loadWIFI() {
        JsonObject wifi = _doc["wifi"];
        strcpy(_wifi.ssid, wifi["ssid"] | WiFi_Settings::ssid);
        strcpy(_wifi.password, wifi["password"] | WiFi_Settings::password);
    }
} conf("config.txt");

#endif  // configuration