#include "defines.h"

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
    pinMode(10, OUTPUT);     // change this to 53 on a mega  // don't follow this!!
    digitalWrite(10, HIGH);  // Add this line
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
    menu.setupLcdWithMenu(rs, rw, en, d0, d1, d2, d3, d4, d5, d6, d7, mainMenu);
    for (size_t i = 0; i < 4; i++) {
        pinMode(menuButtons[i], INPUT);
    }
    digitalWrite(38, HIGH);
    lcdTurnedOn = millis();
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
    //_log.println("hello", ACK);
    //   if (WiFi.begin("Wi-Fi", "Asdfghjkl12") == WL_CONNECTED) {
    //      printf(
    //          "\nSuccesfully connected to:\n\t[SSID]:%s\n\t[Password]:%s\n", "Wi-Fi",
    //          "Asdfghjkl12"
    //      );
    //  }
}
void menuLoop() {
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
                digitalWrite(38, HIGH);
                if (buttonState[i] == HIGH && ((millis() - lcdTurnedOn) < 5 * 1000)) {
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
                    digitalWrite(36, HIGH);
                    delay(100);
                    digitalWrite(36, LOW);
                }
                lcdTurnedOn = millis();
            }
        }
    }
    if ((millis() - lcdTurnedOn) > 5 * 1000) {
        digitalWrite(38, LOW);
    }
    char command = Serial.read();

    switch (command) {
        case UP:
            menu.up();
            break;
        case DOWN:
            menu.down();
            break;
        case LEFT:
            menu.left();
            break;
        case RIGHT:
            menu.right();
            break;
        case ENTER:  // Press enter to go to edit mode : for ItemInput
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
    yield();
}