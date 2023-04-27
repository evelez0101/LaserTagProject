float HIT_CONSTANT = 2.2; 

// LCD Set Up
#include <LiquidCrystal.h>

const int rs = 6, en = 7, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);

  Serial.begin(9600); 
  lcd.setCursor(0, 0);
  lcd.print("Hello World!");

}

void loop() {
  
  int sensorValue = analogRead(A0); 

  float voltage = sensorValue * (5.0 / 1023.0); 
  Serial.println(voltage);

  if(voltage >= 4.2){
  Serial.println("Hit detected");
  lcd.setCursor(0, 0);
  lcd.print("Hit detected!");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("                       ");
  
}

}
