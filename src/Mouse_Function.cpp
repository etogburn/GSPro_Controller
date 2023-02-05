#include "Mouse_Function.h"

Mouse_Function::Mouse_Function(uint8_t type, const char * name, int8_t xVal, int8_t yVal) : Game_Function(name) {
    _type = type;
    if(xVal <= 100 && xVal >= -10) {
        _xVal = xVal;
    } else {
        _xVal = 50;
    }

    if(yVal <= 100 && yVal >= -10) {
        _yVal = yVal;
    } else {
        _yVal = 50;
    }
}

void Mouse_Function::Run(Button_Controller *btn) {
    if(_type == MOUSE_CLICK_FUNCTION) {
        if(btn->State(BTN_RELEASING)) {
            cursor.GoTo(_xVal, _yVal);
        }
    } else if (_type == MOUSE_REL_FUNCTION) {
        if(btn->State(BTN_RELEASING)) {
            cursor.Move(_xVal, _yVal);
        }
    } else if (_type == MOUSE_MULTI_FUNCTION) {
        if(btn->State(BTN_RELEASING)) {

        }
    }
}
