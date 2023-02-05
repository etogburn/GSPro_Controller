#include "Game_Function.h"

Game_Function::Game_Function(const char * name) {
    _name = name;
}

const char * Game_Function::GetName() {
    return _name;
}

void Game_Function::Stop() {
    Mouse.release(MOUSE_ALL);
    Keyboard.releaseAll();
}