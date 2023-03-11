#ifndef OutputMenuWrapper_h
#define OutputMenuWrapper_h

#include <Arduino.h>
#include <generatemenu.h>
#include <ArduinoJson.h>
#include "../menu/mainMenu.h"

MenuItem* OutputMenuWrapper(JsonArray ha, fptrInt outputCallback) {
    MenuItem* Output;
    Output = creatMenu(ha.size(), mainMenu);
    for (size_t i = 0; i < ha.size(); i++) {
        const char* name = ha[i]["name"];
        Output[i + 1] = ItemSubMenu(name, creatMenu(4, Output));
        Output[i + 1][1] = MenuItem(name);
        Output[i + 1][2] = ItemOutput("State:LOW", i, outputCallback);
        Output[i + 1][3] = MenuItem("lastTime");
    }
    return Output;
}
#endif  // OutputMenuWrapper