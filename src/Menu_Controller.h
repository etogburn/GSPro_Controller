#ifndef MENU_CONTROLLER_h
#define MENU_CONTROLLER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Button_Controller.h"
#include "Mouse_Function.h"
#include "Keyboard_Function.h"
#include "Menu_Function.h"

#define LCD_ROWS 4
#define LCD_COLS 20
#define LCD_I2C_ADDRESS 0x27
#define FUNCTION_COUNT 10

class Menu_Controller : private LiquidCrystal_I2C {
public:
    Menu_Controller(Menu_Function *[], Game_Function *[], Button_Controller *[], uint8_t, uint8_t);
    void SetMenu(Game_Function * []);
    uint8_t GetActiveMenu();
    void Run();

private:
    void PrintMenu();
    void PrintMainMenu();
    void PrintFunctionRow(int8_t, uint8_t, uint8_t);
    void PrintRow(int8_t, const char *, byte, const char *, byte);
    void LoadCustomChars();
    void UpdateButtons();
    void RunActions();
    bool ButtonTimeoutPress();
    uint8_t GetCharForButton(uint8_t);
    Game_Function *_menu[FUNCTION_COUNT];
    Button_Controller *_btns[FUNCTION_COUNT];
    Menu_Function *_mainMenu[FUNCTION_COUNT];
    uint8_t _activeMenu = 0;
    uint8_t _maxMenus = 0;
    //bool _mainMenu = false;
};

#endif