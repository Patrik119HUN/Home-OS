#include "defines.h"
Button proba(30);
void onButtonCommand(HAButton* sender) {
    if (sender == &buttonA) {
        Serial.println("button A pressed");
    } else if (sender == &buttonB) {
        // button B was clicked, do your logic here
        Serial.println("button B pressed");
    }
}
void menuLoop();
void setup() {
    Serial.begin(BAUD_RATE);
    pinMode(36, OUTPUT);
    pinMode(38, OUTPUT);
    proba.begin();
    display.init();

    for (size_t i = 0; i < 9; i++) {
        Serial.println(Splash_screen[i]);
    }
    printf("\nVersion:\n\t %s\n", VERSION);
    printf("Built On:\n \t[Date]: %s\n\t[Time]: %s\n", __DATE__, __TIME__);
    printf("Made by:\n\tTukacs Patrik\n");
#ifdef RTC_MODULE
    while (!rtc.begin()) {
        Serial.println(F("Failed to initialize RTC library"));
        Serial.println(F("Retrying RTC initializaton!"));
        delay(1000);
        // ntp.begin();
    }

#endif
#ifdef WIFI_MODULE
    Serial1.begin(115200);
    WiFi.init(Serial1);
    while (WiFi.status() == WL_NO_MODULE) {
        _log.println("Communication with WiFi module failed!", LogLevel::ERROR, rtc.now());
        _log.println("Retrying WIFI initializaton!", LogLevel::ERROR, rtc.now());
        display.print(0b01011011);
        delay(1000);
    }
    _log.println("WIFI initializaton OK!", LogLevel::ACK, rtc.now());
    byte mac[6];
    WiFi.macAddress(mac);
    printf("[Wi-Fi MAC]: \n\t");
    Serial.print(mac2String(mac));
    Serial.println();
    Serial.println("Scanning available networks...");
    listNetworks();
#endif
#ifdef SD_MODULE
    pinMode(SD_PIN, OUTPUT);     // change this to 53 on a mega  // don't follow this!!
    digitalWrite(SD_PIN, HIGH);  // Add this line
    while (!SD.begin(SD_PIN)) {
        _log.println("Failed to initialize SD library", LogLevel::ERROR, rtc.now());
        _log.println("Retrying SD initializaton!", LogLevel::ERROR, rtc.now());
        display.print(0b00000110);
        delay(1000);
    }
    _log.println("SD initializaton OK!", LogLevel::ACK, rtc.now());
    conf.begin();
    conf.loadMQTT();
    conf.loadWIFI();
    mqtt.begin(conf._mqtt.server, conf._mqtt.username, conf._mqtt.password);
#endif
#ifdef LCD_MODULE
    menu.begin(mainMenu);
#endif
    if (WiFi.begin("Wi-Fi", "Asdfghjkl12") == WL_CONNECTED) {
        printf(
            "\nSuccesfully connected to:\n\t[SSID]:%s\n\t[Password]:%s\n", "Wi-Fi", "Asdfghjkl12"
        );
    }
    device.setName("HomeOS");
    device.setSoftwareVersion(VERSION);

    // optional properties
    buttonA.setIcon("mdi:fire");
    buttonA.setName("Click me A");
    buttonB.setIcon("mdi:home");
    buttonB.setName("Click me B");

    // press callbacks
    buttonA.onCommand(onButtonCommand);
    buttonB.onCommand(onButtonCommand);

    Scheduler.startLoop(menuLoop);
    display.clear();
}
void loop() {
    mqtt.loop();
    yield();
    // UpdateNTP(wifi_udp, &ntp, &rtc);

    // ntp.update();
}

void menuLoop() {
    menu.menuLoop();
    yield();
}