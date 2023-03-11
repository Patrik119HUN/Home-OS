#ifndef configuration_h
#define configuration_h

#include <LoadJSONFromSD.h>

#include "Home_Assistant/Home_Assistant.h"
#include "MQTT/MQTT.h"
#include "helper/OutputMenuWrapper.h"
#include "menu/mainMenu.h"
#include "menu/Callback/OutputCallback.h"
#include "network/Ethernet.h"
#include "network/WIFI.h"
#include "user_config.h"
extern MenuItem mainMenu[];
void outputCallback(uint8_t pin);

class Configuration : public LoadJSONFromSD {
   public:
    char hostname[64];
    char time_zone[9];
    Wifi _wifi;
    MQTT _mqtt;
    Home_Assistant* _ha;
    using LoadJSONFromSD::LoadJSONFromSD;
    void loadMQTT() {
        JsonObject mqtt = load("mqtt");
        strcpy(_mqtt.server, mqtt["server"]);
        strcpy(_mqtt.password, mqtt["password"]);
        strcpy(_mqtt.username, mqtt["username"]);
        strcpy(_mqtt.id, mqtt["id"]);
        _mqtt.port = mqtt["port"];
        JsonArray ha = mqtt["Home_assistant"];
        mainMenu[2].setSubMenu(OutputMenuWrapper(ha, outputCallback));
    }
    void loadWIFI() {
        JsonObject wifi = load("wifi");
        strcpy(_wifi.ssid, wifi["ssid"] | WiFi_Settings::ssid);
        strcpy(_wifi.password, wifi["password"] | WiFi_Settings::password);
    }
} conf("config.txt");


#endif  // configuration