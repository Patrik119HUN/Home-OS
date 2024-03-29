#ifndef configuration_h
#define configuration_h

#include <LoadJSONFromSD.h>
#include "../interface/Home_Assistant/Output_struct.h"
#include "menu/mainMenu.h"
#include "user_config.h"
#include "Home_Assistant/Home_Assistant.h"
#include "MQTT/MQTT.h"
#include "network/Ethernet.h"
#include "network/WIFI.h"
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

        MenuItem* Output;
        Output = creatMenu(ha.size(), mainMenu);
        for (size_t i = 0; i < ha.size(); i++) {
            const char* name = ha[i]["name"];
            Output[i + 1] = ItemSubMenu(name, creatMenu(4, Output));
            Output[i + 1][1] = MenuItem(name);
            Output[i + 1][2] = ItemOutput("State:LOW",i,outputCallback);
            Output[i + 1][3] = MenuItem("lastTime");
        }
        mainMenu[2].setSubMenu(Output);
    }
    void loadWIFI() {
        JsonObject wifi = load("wifi");
        strcpy(_wifi.ssid, wifi["ssid"] | WiFi_Settings::ssid);
        strcpy(_wifi.password, wifi["password"] | WiFi_Settings::password);
    }
} conf("config.txt");

void outputCallback(uint8_t pin) {
    // Outputs->setItems(proba);
    //uint32_t pin = conf._ha[pos].pin;
    //String name = conf._ha[0].name;
    //String names[] = {_out[0].name, _out[1].name};
    Serial.print(pin);
    _out[pin].toggle();
    //Serial.println(_out[pos].name);
    if (_out[pin].state == HIGH) {
        mainMenu[2][pin+1][2].setText("State:HIGH");
    } else {
        mainMenu[2][pin+1][2].setText("State:LOW");
    }
}
#endif  // configuration