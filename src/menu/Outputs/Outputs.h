#ifndef Outputs_h
#define Outputs_h

#include <Arduino.h>
#include <LcdMenu.h>

#include "../../IO/Output/Binary.h"
#include "../../interface/configuration.h"
#include "../mainMenu.h"
#include "../../interface/Home_Assistant/Output_struct.h"

void colorsCallback(uint8_t pos);
String outputs[] = {String(_out[0].name), String(_out[1].name)};
String proba[] = {"hello","bello"};
extern MenuItem mainMenu[];

MenuItem Outputs[] = {
    ItemHeader(mainMenu), ItemList("Out", outputs, 2, colorsCallback), MenuItem("State:"), ItemFooter()};

void colorsCallback(uint8_t pos) {
    //Outputs->setItems(proba);
    uint32_t pin = conf._ha[pos].pin;
    String name = String(conf._ha[0].name);
    _out[pin].toggle();
    if (_out[pin].state == HIGH) {
        Outputs[2].setText("State:HIGH");
    } else {
        Outputs[2].setText("State:LOW");
    }
}
#endif  // Outputs