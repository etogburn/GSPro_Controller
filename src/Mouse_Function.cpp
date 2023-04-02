#include "Mouse_Function.h"

Mouse_Function::Mouse_Function(uint8_t type, const char * name, int8_t xVal, int8_t yVal) : Game_Function(name) {
    _type = type;
    if(xVal <= 100 && xVal >= -10) {
        _xVal = xVal;
    } else {
        _moveEnabled = false;
        _xVal = 50;
    }

    if(yVal <= 100 && yVal >= -10) {
        _yVal = yVal;
    } else {
        _moveEnabled = false;
        _yVal = 50;
    }
}

void Mouse_Function::Run(Button_Controller *btn) {
    if(_type == MOUSE_ABS_FUNCTION) {
        if(btn->State(BTN_RELEASING)) {
            cursor.GoTo(_xVal, _yVal);
        }
    } else if (_type == MOUSE_REL_FUNCTION) {
        if(btn->State(BTN_PRESSED)) {
            cursor.Move(_xVal, _yVal);
            delay(20);
        }
    } else if (_type == MOUSE_MULTI_FUNCTION) {
        if(btn->State(BTN_RELEASING)) {

        }
    } else if (_type == MOUSE_CLICK_FUNCTION) {
        if(btn->State(BTN_RELEASING)) {
            if(_moveEnabled) cursor.GoTo(_xVal, _yVal);
            cursor.Click();
        }
    }
}
