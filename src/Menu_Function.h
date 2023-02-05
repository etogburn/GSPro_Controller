#ifndef MENU_FUNCTION_h
#define MENU_FUNCTION_h

#include <Arduino.h>
#include "Game_Function.h"
#include "Button_Controller.h"

#define KEY_PRESS_FUNCTION 0
#define KEY_HOLD_FUNCTION 1
#define DOUBLE_KEY_FUNCTION 2

class Menu_Function: public Game_Function {
public:
    Menu_Function(uint8_t, const char *, uint8_t);
    void Run(Button_Controller*);
    uint8_t GetIndex();

private:
    uint8_t _type;
    uint8_t _menuIndex;
};

#endif