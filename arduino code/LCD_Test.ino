// LCD1602 to Arduino Uno connection example

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
String top = "Ammunition: ";
int ammo = 90;
String bottom = "Health: "; 
String health = "######"; 


void setup() {
  // Initialozes LCD
  lcd.begin(16, 2);
}

void loop() 
{
  displayScreen();

}

// Displays Ammo on top and Health on bottom
void displayScreen()
{
  lcd.setCursor(0,0);
  lcd.print(top + ammo);
  lcd.setCursor(0,1);
  lcd.print(bottom + health);
}
