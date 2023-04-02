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
#define GAME_FUNCTIONS 34
#define NUM_OF_MENUS 2
bool menuSelectMode = true;
uint8_t activeMenu = 0;
const char * menuName[4] = {"Standard", "Mouse", "N/A", "N/A"};
const uint8_t menuBtns[NUM_OF_MENUS] = {9,8}; //set the different menus
const uint8_t menuBtn1 = 9; //2 buttons to press at the same time to get to the menu change menu
const uint8_t menuBtn2 = 8;


Game_Function *game[GAME_FUNCTIONS] = {
  new Mouse_Function(MOUSE_REL_FUNCTION, "^", 0, -1),
  new Mouse_Function(MOUSE_REL_FUNCTION, "v", 0, 1),
  new Mouse_Function(MOUSE_REL_FUNCTION, "<", -1, 0),
  new Mouse_Function(MOUSE_REL_FUNCTION, ">", 1, 0),
  new Mouse_Function(MOUSE_REL_FUNCTION, "^^^", 0, -5),
  new Mouse_Function(MOUSE_REL_FUNCTION, "vvv", 0, 5),
  new Mouse_Function(MOUSE_REL_FUNCTION, "<<<", -5, 0),
  new Mouse_Function(MOUSE_REL_FUNCTION, ">>>", 5, 0),
  new Mouse_Function(MOUSE_ABS_FUNCTION, "Center", 50, 50),
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
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "DR-Bot", 20, 20),
  new Mouse_Function(MOUSE_CLICK_FUNCTION, "Click", -100, -100)
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
    game[6],
    game[7],
    game[5],
    game[4],
    game[8],
    game[33]
  }
};