#include "Keyboard_Function.h"

Keyboard_Function::Keyboard_Function(uint8_t type, const char * name, char firstPress, char secondPress) : Game_Function(name) {
    _type = type;
    _firstKey = firstPress;
    _secondKey = secondPress;
    Keyboard.begin();
}

void Keyboard_Function::Run(Button_Controller *btn) {
    if(_type == KEY_PRESS_FUNCTION) {
        if(btn->State(BTN_RELEASING)) {
            Keyboard.print(_firstKey);
        }
    } else if(_type == KEY_HOLD_FUNCTION) {
        if(btn->State(BTN_PRESSING)) {
            Keyboard.press(_firstKey);
        } else if(btn->State(BTN_RELEASING)) {
            Keyboard.release(_firstKey);
        }
    } else if(_type == DOUBLE_KEY_FUNCTION) {
        if(btn->State(BTN_PRESSING)) {
        } else if(btn->State(BTN_RELEASING)) {
            Keyboard.press(_firstKey);
            Keyboard.press(_secondKey);
            Keyboard.release(_firstKey);
            Keyboard.release(_secondKey);
        }
    }
}