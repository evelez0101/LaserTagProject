// LCD1602 to Arduino Uno connection example

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int AMMO = 90;
String t = "Ammunition: " + (String)AMMO;
String r = "#### Reload ####";
String b = "Health: ####### ";

void setup() {
  // Set up 16 by 2 character matrix 
  lcd.begin(16, 2);
  // you can now interact with the LCD, e.g.:
  screen();
}

void loop() {

}

void screen() // Need to implment dynamic screen fucntion later
{
  // Sets cursor to print top row 
  lcd.setCursor(0,0);
  lcd.print(t);

  if (AMMO == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(r);
  }

  // Sets cursor to print bottom row
  lcd.setCursor(0, 1);
  lcd.print(b);
}

void shoot()
{
  AMMO--;
  t = "Ammunition: " + (String)AMMO;
}
