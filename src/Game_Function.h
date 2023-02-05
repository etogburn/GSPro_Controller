#ifndef GAME_FUNCTION_h
#define GAME_FUNCTION_h

#include <Arduino.h>
#include "Button_Controller.h"
#include <Mouse.h>
#include <Keyboard.h>

class Game_Function {
public:
    Game_Function(const char *);
    const char * GetName();
    virtual void Run(Button_Controller*) = 0;
    void Stop();

private:
    const char * _name;
};

#endif