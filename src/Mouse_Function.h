#ifndef MOUSE_FUNCTION_h
#define MOUSE_FUNCTION_h

#include <Arduino.h>
#include "Game_Function.h"
#include "Mouse_Controller.h"
#include "Button_Controller.h"

#define SCREEN_WIDTH 3000
#define SCREEN_HEIGHT 2000
#define SCREEN_SCALE 4 //windows scaling divided by 50

#define MOUSE_CLICK_FUNCTION 0
#define MOUSE_DRAG_FUNCTION 1
#define MOUSE_REL_FUNCTION 2
#define MOUSE_MULTI_FUNCTION 3

class Mouse_Function: public Game_Function {
public:
    Mouse_Function(uint8_t, const char *, int8_t, int8_t);
    void Run(Button_Controller*);
private:
    Mouse_Controller cursor = Mouse_Controller(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_SCALE);
    uint8_t _type;
    int8_t _xVal;
    int8_t _yVal;
};

#endif