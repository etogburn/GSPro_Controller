#include "Menu_Controller.h"
#include "Custom_Characters.h"

Menu_Controller::Menu_Controller(Menu_Function *mainMenu[], Game_Function *game[], Button_Controller *btn[], uint8_t maxMenus, uint8_t currentMenu) : 
                LiquidCrystal_I2C(LCD_I2C_ADDRESS, LCD_COLS, LCD_ROWS) {
    *_btns = *btn;
    _maxMenus = maxMenus;
    _activeMenu = currentMenu;
    *_menu = *game;
    *_mainMenu = *mainMenu;
    
    init();
    backlight();
    LoadCustomChars();
    home();
};

void Menu_Controller::Run() {
    UpdateButtons();
    
    if(ButtonTimeoutPress()) {
        //_mainMenu = true;
    }

    // if(_mainMenu) {
    //     PrintMainMenu();
    // } else {
    //     RunActions();
    //     PrintMenu();
    // }
    
};

void Menu_Controller::SetMenu(Game_Function *newMenu[]) {
    *_menu = *newMenu;
};

uint8_t Menu_Controller::GetActiveMenu() {
    return _activeMenu;
};

void Menu_Controller::UpdateButtons() {
    for(uint8_t i = 0; i < FUNCTION_COUNT; i++) {
        _btns[i]->DoEvents();
    }
};

void Menu_Controller::RunActions() {
    for(uint8_t i = 0; i < FUNCTION_COUNT; i++) {
        _menu[i]->Run(_btns[i]);
    }
};

bool Menu_Controller::ButtonTimeoutPress() {
    for(uint8_t i = 0; i < FUNCTION_COUNT; i++) {
        if(_btns[i]->State(BTN_TIMEOUT_PRESS)) return true;
    }
    return false;
}

void Menu_Controller::PrintMenu() {
  static long lastRun = 0;
  static int8_t firstRow = 0;
  if(millis() - lastRun > 2000) {
    if(firstRow == 0) firstRow++;
    else firstRow--;

    PrintFunctionRow(firstRow-1, 9,8);
    PrintFunctionRow(firstRow  , 0,7);
    PrintFunctionRow(firstRow+1, 1,6);
    PrintFunctionRow(firstRow+2, 2,5);
    PrintFunctionRow(firstRow+3, 3,4);
    
    lastRun = millis();
  }
};

//=========================================================================================
//=========================================================================================
//=========================================================================================
//=========================================================================================
//=========================================================================================
//=========================================================================================
//=========================================================================================
void Menu_Controller::PrintMainMenu() {
    clear();
    print("Menu- ");
    //print(_menuName[_activeMenu]);
    static int8_t firstRow = 2;
    //PrintRow(firstRow-1, _menuName[0], CHAR_UP, _menuName[1],  CHAR_UP);
    //PrintRow(firstRow, _menuName[2], CHAR_UPLEFT, _menuName[3], CHAR_UPRIGHT);
    setCursor(0,3);
    print("Long Press to Go");
};
//=========================================================================================
//=========================================================================================
//=========================================================================================
//=========================================================================================
//=========================================================================================
//=========================================================================================
//=========================================================================================

void Menu_Controller::PrintFunctionRow(int8_t rowNum, uint8_t firstBtn, uint8_t secondBtn) {
    PrintRow(rowNum, _menu[firstBtn]->GetName(),GetCharForButton(firstBtn),
            _menu[secondBtn]->GetName(),GetCharForButton(secondBtn));
};

void Menu_Controller::PrintRow(int8_t rowNum, const char * firstName, byte firstChar, const char * secondName, byte secondChar) {
  if(rowNum > LCD_ROWS - 1 || rowNum < 0) return;
  uint8_t firstLen = strlen(firstName);
  uint8_t secondLen = strlen(secondName);
  uint8_t leftOver = LCD_COLS - firstLen - secondLen - 2;
  setCursor(0,rowNum);
  write(firstChar);
  print(firstName);
  for(uint8_t i = 0; i < leftOver; i++) {
    print(" ");
  }
  print(secondName);
  write(secondChar);
}

void Menu_Controller::LoadCustomChars() {
    
  createChar(CHAR_UP, _upArrow);
  createChar(CHAR_UPRIGHT, _upRightArrow);
  createChar(CHAR_RIGHT, _rightArrow);
  createChar(CHAR_DOWNRIGHT, _downRightArrow);
  createChar(CHAR_DOWN, _downArrow);
  createChar(CHAR_DOWNLEFT, _downLeftArrow);
  createChar(CHAR_LEFT, _leftArrow);
  createChar(CHAR_UPLEFT, _upLeftArrow);
};

uint8_t Menu_Controller::GetCharForButton(uint8_t btnNum) {
    const uint8_t _btnCharMap[FUNCTION_COUNT] = {
        CHAR_UPLEFT, 
        CHAR_LEFT, 
        CHAR_DOWNLEFT, 
        CHAR_DOWN, 
        CHAR_DOWN, 
        CHAR_DOWNRIGHT, 
        CHAR_RIGHT, 
        CHAR_UPRIGHT, 
        CHAR_UP, 
        CHAR_UP
    };
    return _btnCharMap[btnNum];
}