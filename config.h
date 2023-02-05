#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keyboard.h>
#include "src/Button_Controller.h"
#include "src/Mouse_Controller.h"
#include "src/Game_Function.h"
#include "src/Keyboard_Function.h"
#include "src/Mouse_Function.h"
#include "Custom_Chars.h"

#define MENU_FUNCTIONS 10
#define GAME_FUNCTIONS 33
#define NUM_OF_MENUS 2
bool menuSelectMode = true;
uint8_t activeMenu = 1;
const char * menuName[4] = {"Standard", "Mouse", "N/A", "N/A"};
const uint8_t menuBtns[NUM_OF_MENUS] = {9,8};

Game_Function *game[GAME_FUNCTIONS] = {
  new Mouse_Function(MOUSE_REL_FUNCTION, "2y", 0, -2),
  new Mouse_Function(MOUSE_REL_FUNCTION, "-2y", 0, 2),
  new Mouse_Function(MOUSE_REL_FUNCTION, "-2x", -2, 0),
  new Mouse_Function(MOUSE_REL_FUNCTION, "2x", 2, 0),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "2020", 20, 20),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "4040", 40, 40),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "6060", 60, 60),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "8080", 80, 80),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "9090", 90, 90),
  new Keyboard_Function(KEY_HOLD_FUNCTION, "Aim ^", KEY_UP_ARROW, 0),
  new Keyboard_Function(KEY_HOLD_FUNCTION, "Aim v", KEY_DOWN_ARROW, 0),
  new Keyboard_Function(KEY_HOLD_FUNCTION, "Aim <", KEY_LEFT_ARROW, 0),
  new Keyboard_Function(KEY_HOLD_FUNCTION, "Aim >", KEY_RIGHT_ARROW, 0),
  new Keyboard_Function(KEY_PRESS_FUNCTION, "Flyover", 'o', 0), 
  new Keyboard_Function(KEY_PRESS_FUNCTION, "Scout", 'j', 0), 
  new Keyboard_Function(KEY_PRESS_FUNCTION, "Club-dn", 'k', 0), 
  new Keyboard_Function(KEY_PRESS_FUNCTION, "Club-up", 'i', 0), 
  new Keyboard_Function(KEY_HOLD_FUNCTION, "FF>>", ' ', 0),
  new Keyboard_Function(DOUBLE_KEY_FUNCTION, "Mulligan", KEY_RIGHT_CTRL, 'm'),
  new Keyboard_Function(KEY_PRESS_FUNCTION, "Scorecard", 't', 0), 
  new Keyboard_Function(KEY_PRESS_FUNCTION, "Pin Ind.", 'p', 0), 
  new Keyboard_Function(KEY_PRESS_FUNCTION, "Hide UI", 'h', 0), 
  new Keyboard_Function(KEY_PRESS_FUNCTION, "Show UI", KEY_ESC, 0), 
  new Keyboard_Function(KEY_PRESS_FUNCTION, "Heat Map", 'y', 0), 
  new Keyboard_Function(KEY_PRESS_FUNCTION, "GreenGrid", 'g', 0),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "Drop", 20, 20),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "Options", 20, 20),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "Rehit", 20, 20),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "Sim Drop", 20, 20),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "LBallTee", 20, 20),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "RBallTee", 20, 20),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "DR-Top", 20, 20),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "DR-Bot", 20, 20)
};

Game_Function *menu[NUM_OF_MENUS][MENU_FUNCTIONS] = {
  {
    game[9],
    game[10],
    game[11],
    game[12],
    game[13],
    game[14],
    game[15],
    game[16],
    game[17],
    game[18]
  },
  {
    game[0],
    game[1],
    game[2],
    game[3],
    game[4],
    game[5],
    game[6],
    game[7],
    game[8],
    game[9]
  }
};