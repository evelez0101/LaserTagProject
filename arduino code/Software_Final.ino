/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  NOTE: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL29EhZmcUE"
#define BLYNK_TEMPLATE_NAME "Laser Tag"
#define BLYNK_AUTH_TOKEN "fopAbVat1pMHim9Gs81X4J0k1aPG1DXE"


#include <LiquidCrystal.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>


// New Constant
const double HIT_CONSTANT = 4.2; 

// LCD Set Up
const int rs = 6, en = 7, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Strings to Display
String top = "Soldier 1      ";
String bottom = "Health: ";

int health = 0;
String name = "Soldier 1";
int score = 500; 

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Columbia University";
char pass[] = "";

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

void setup()
{
  // LCD Protocol 
  lcd.begin(16, 2);
  displayScreen();

  // Debug console
  Serial.begin(9600);
  delay(10);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);
}

void sendInfo()
{
  
  //Player 1
  Blynk.virtualWrite(V1,health);
  Blynk.virtualWrite(V5,score);
  Blynk.virtualWrite(V2,name);
  
  /*
  // Player 2
  Blynk.virtualWrite(V9,health);
  Blynk.virtualWrite(V6,score);
  Blynk.virtualWrite(V0,name);
  */
}

void loop()
{
  if (health == 0)
  {
    // Reset the Game
    reset();
  }

  Blynk.run();

  // Updates and Displays 
  displayScreen();
  
  // Sends Info to Blynk
  sendInfo();

   // Looks for Hit 
  if (health != 0)
  {
    actionListner();
  }

}

void reset()
{   
  // Display the death screen and sends info 
  displayScreen();
  sendInfo();

  // Wait 10 seconds 
  delay(10000);

  // Score Health Reset 
  score = 1000;  
  health = 5;   
}

void actionListner()
{

  // Infinite Loop
  for(;;)
  {
    if (sensor())
    {
      // Decrement by 1 
      health--;
      score -= 150; 
      break;   
    }
  }

}

void displayScreen()
{
  // Death Screen 
  if (health == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("   YOU DIED!    ");
    lcd.setCursor(0, 1);
    lcd.print("                "); 
  }
  // When Health is Greater than 0
  else if (health > 0)
  {
    lcd.setCursor(0, 0);
    lcd.print(top);
    lcd.setCursor(0, 1);
    lcd.print(bottom + health);

  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("      Error     ");
  }

}

bool sensor()
{
  // Value of A0 (Analoge Pin)
  long sensorValue = analogRead(A0); 

  double voltage = sensorValue * (5.0 / 1023.0); 
  
  // If the Constant is exceeded then its a hit
  if(voltage >= HIT_CONSTANT)
  {
    delay(1000);
    return true;
  }
  else 
  {
    return false;
  }

}
