#include "Menu_Function.h"

Menu_Function::Menu_Function(uint8_t type, const char * name, uint8_t menuIndex) : Game_Function(name) {
    _type = type;
    _menuIndex = menuIndex;
}

void Menu_Function::Run(Button_Controller *btn) {
    
}

uint8_t Menu_Function::GetIndex() {
    return _menuIndex;
}