#ifndef Outputs_h
#define Outputs_h

#include <Arduino.h>
#include <LcdMenu.h>

#include "../../IO/Output/Binary.h"
#include "../../interface/Home_Assistant/Output_struct.h"
//#include "../../interface/configuration.h"
#include "../mainMenu.h"
void togglePin(uint8_t isOn);
void colorsCallback(uint8_t pos);
extern MenuItem mainMenu[];
extern MenuItem Outputs[];
MenuItem Out_Set[] = {
    ItemHeader(Outputs),
    ItemToggle("Pin",togglePin),  
    ItemFooter()
};
MenuItem Outputs[] = {
    ItemHeader(mainMenu),
    ItemSubMenu("Out_1",Out_Set),
    ItemSubMenu("Out_2",Out_Set),
    ItemSubMenu("Out_3",Out_Set),
    ItemSubMenu("Out_4",Out_Set),
    ItemSubMenu("Out_5",Out_Set),
    //ItemList("Out", outputs, 2, colorsCallback), MenuItem("State:"),
    ItemFooter()};
void colorsCallback(uint8_t pos) {
    // Outputs->setItems(proba);
    //uint32_t pin = conf._ha[pos].pin;
    //String name = conf._ha[0].name;
    //String names[] = {_out[0].name, _out[1].name};
    //_out[pin].toggle();
    //Serial.println(_out[pos].name);
    //if (_out[pin].state == HIGH) {
    //    Outputs[2].setText("State:HIGH");
   // } else {
   //     Outputs[2].setText("State:LOW");
  //  }
}
void togglePin(uint8_t isOn){

}
#endif  // Outputs