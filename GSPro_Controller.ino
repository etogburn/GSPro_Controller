#include "config.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keyboard.h>
#include "src/Menu_Controller.h"
#include "src/Button_Controller.h"

LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS,LCD_COLS,LCD_ROWS);  

Button_Controller *buttons[MENU_FUNCTIONS] = {
    new Button_Controller(4),
    new Button_Controller(5),
    new Button_Controller(6),
    new Button_Controller(7),
    new Button_Controller(8),
    new Button_Controller(9),
    new Button_Controller(10),
    new Button_Controller(11),
    new Button_Controller(12),
    new Button_Controller(13)
};

Menu_Controller menus = Menu_Controller(mainMenuList, menuList[ACTIVE_MENU], buttons, NUM_OF_MENUS, ACTIVE_MENU);

void setup() {

}

void loop() {
  menus.Run();
  menus.SetMenu(menuList[menus.GetActiveMenu()]);
}

//not yet implemented
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
    lcd.print(buttons[i]->State(), BIN);
    lcd.print(" ");
  }
  delay(250); 
}
