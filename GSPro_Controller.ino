/*********************

Mouse absolute location class - mouse_controller
keyboard shortcuts in the keyboard class
game functions class
buttons point to game functions dependent on the current controller mode
buttons and game functions join together in the main program

**********************/

#include "config.h"

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27

Button_Controller buttons[MENU_FUNCTIONS] = {
    Button_Controller(4),
    Button_Controller(5),
    Button_Controller(6),
    Button_Controller(7),
    Button_Controller(8),
    Button_Controller(9),
    Button_Controller(10),
    Button_Controller(11),
    Button_Controller(12),
    Button_Controller(13)
};

void setup() {
  lcd.init();
  lcd.backlight();
  loadCustomChars();
  lcd.home();
  printMenuChange(false);
}

void loop() {
  if((buttons[menuBtn1].State(BTN_PRESSED) && buttons[menuBtn2].State(BTN_RELEASING)) ||
     (buttons[menuBtn2].State(BTN_PRESSED) && buttons[menuBtn1].State(BTN_RELEASING)) ||
     (buttons[menuBtn2].State(BTN_RELEASING) && buttons[menuBtn1].State(BTN_RELEASING)) ) {
    menu[activeMenu][menuBtn1]->Stop();
    menu[activeMenu][menuBtn2]->Stop();
    printMenuChange(false);

    while(buttons[menuBtn2].State(BTN_PRESSED) || buttons[menuBtn1].State(BTN_PRESSED) || 
          buttons[menuBtn1].State(BTN_RELEASING) || buttons[menuBtn2].State(BTN_RELEASING)) {
      buttons[menuBtn1].DoEvents();
      buttons[menuBtn2].DoEvents();
    }
        
    menuSelectMode = true;   
  }

  for(uint8_t i = 0; i < MENU_FUNCTIONS; i++) {
    buttons[i].DoEvents();
    if(menuSelectMode) { 
      if(i < NUM_OF_MENUS && buttons[menuBtns[i]].State(BTN_RELEASING)) {
        activeMenu = i; 
        menuSelectMode = false;
      } else { 
        bool _usedMenuBtn = false;
        for(uint8_t j = 0; j < NUM_OF_MENUS; j++) {
          if(i == menuBtns[j]) _usedMenuBtn = true; 
        }
        if(!_usedMenuBtn && buttons[i].State(BTN_RELEASING)) menuSelectMode = false;
      }
    } else {
      if(i < NUM_OF_MENUS && buttons[menuBtns[i]].State(BTN_TIMEOUT_PRESS)) {
        activeMenu = i;
        menu[activeMenu][menuBtns[i]]->Stop();
        printMenuChange(true);
      } else {
        menu[activeMenu][i]->Run(&buttons[i]);
      }
    }
    
  }                                                                             
  //printButtons();
  if(!menuSelectMode) printFunctions();
}

void printMenuChange(bool useDelay) {
  lcd.clear();
  lcd.print("Menu- ");
  lcd.print(menuName[activeMenu]);
  static int8_t firstRow = 2;
  printRow(firstRow-1, menuName[0], CHAR_UP, menuName[1],  CHAR_UP);
  printRow(firstRow, menuName[2], CHAR_UPLEFT, menuName[3], CHAR_UPRIGHT);
  lcd.setCursor(0,3);
  lcd.print("Press to Go");
  if(useDelay) delay(3000);
}

void printFunctions() {
  static long lastRun = 0;
  static int8_t firstRow = 0;
  if(millis() - lastRun > 2000) {
    if(firstRow == 0) firstRow++;
    else firstRow--;

    printRow(firstRow-1, menu[activeMenu][9]->GetName(), CHAR_UP, menu[activeMenu][8]->GetName(), CHAR_UP);
    printRow(firstRow, menu[activeMenu][0]->GetName(), CHAR_UPLEFT, menu[activeMenu][7]->GetName(), CHAR_UPRIGHT);
    printRow(firstRow+1, menu[activeMenu][1]->GetName(), CHAR_LEFT, menu[activeMenu][6]->GetName(), CHAR_RIGHT);
    printRow(firstRow+2, menu[activeMenu][2]->GetName(), CHAR_DOWNLEFT, menu[activeMenu][5]->GetName(), CHAR_DOWNRIGHT);
    printRow(firstRow+3, menu[activeMenu][3]->GetName(), CHAR_DOWN, menu[activeMenu][4]->GetName(), CHAR_DOWN);
    
    lastRun = millis();
  }
}

void printRow(int8_t rowNum, const char * firstName, byte firstChar, const char * secondName, byte secondChar) {
  if(rowNum > 3 || rowNum < 0) return;
  uint8_t firstLen = strlen(firstName);
  uint8_t secondLen = strlen(secondName);
  uint8_t leftOver = 20 - firstLen - secondLen - 2;
  lcd.setCursor(0,rowNum);
  lcd.write(firstChar);
  lcd.print(firstName);
  for(uint8_t i = 0; i < leftOver; i++) {
    lcd.print(" ");
  }
  lcd.print(secondName);
  lcd.write(secondChar);
}

void printButtons() {
  lcd.setCursor(0,0);
  for(uint8_t i = 0; i < 10; i++) {
    if(i==4) {
      lcd.print("   ");
      lcd.setCursor(0,1);
    }
    else if(i==8) {
      lcd.print("   ");
      lcd.setCursor(0,2);
    }
    lcd.print(i);
    lcd.print("-");
    lcd.print(buttons[i].State(), BIN);
    lcd.print(" ");
  }
  delay(250);
}

void loadCustomChars() {
  lcd.createChar(CHAR_UP, upArrow);
  lcd.createChar(CHAR_UPRIGHT, upRightArrow);
  lcd.createChar(CHAR_RIGHT, rightArrow);
  lcd.createChar(CHAR_DOWNRIGHT, downRightArrow);
  lcd.createChar(CHAR_DOWN, downArrow);
  lcd.createChar(CHAR_DOWNLEFT, downLeftArrow);
  lcd.createChar(CHAR_LEFT, leftArrow);
  lcd.createChar(CHAR_UPLEFT, upLeftArrow);
}