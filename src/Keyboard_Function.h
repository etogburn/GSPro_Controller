#ifndef KEYBOARD_FUNCTION_h
#define KEYBOARD_FUNCTION_h

#include <Arduino.h>
#include "Game_Function.h"
#include <Keyboard.h>
#include "Button_Controller.h"

#define KEY_PRESS_FUNCTION 0
#define KEY_HOLD_FUNCTION 1
#define DOUBLE_KEY_FUNCTION 2

class Keyboard_Function: public Game_Function {
public:
    Keyboard_Function(uint8_t, const char *, char, char);
    void Run(Button_Controller*);
private:
    uint8_t _type;
    char _firstKey;
    char _secondKey;
};

#endif