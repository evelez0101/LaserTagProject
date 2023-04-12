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
#define BLYNK_AUTH_TOKEN "rJzWtffKDatiPPb2EXNYqz4vK_XgDmJS"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal.h>
#include <ezButton.h>

// Pin Set up (ESP 32 Set Up)
int Reciever = 34; 
int Light = 13;
int Buzzer = 6;

// LCD Set Up
const int rs = 19, en = 23, d4 = 18, d5 = 17, d6 = 16, d7 = 15;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Strings to Display
String top = "Player 1";
String bottom = "Health: ";

// Game Elements
int health = 5;
String name = "Player 1";
ezButton hitSim(Reciever);

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Columbia University";
char pass[] = "";

void setup()
{
  // Tester Button
  hitSim.setDebounceTime(50);
  
  // LED (If we use)
  pinMode(Light,OUTPUT);

  // LCD Protocol 
  lcd.begin(16, 2);
  
  // Debug console
  Serial.begin(9600);

  // Blynk Protocol
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

// Sends Health Information to Blynk Server 
void sendHealth()
{
  Blynk.virtualWrite(V1,health);
}

void loop()
{
  // Run the Blynk Scipt 
  Blynk.run();
  
  // Updates and Displays 
  displayScreen();
  
  // Sends Player Name 
  Blynk.virtualWrite(V2,name);
  
  // Looks for Hit 
  actionListner();
  
  // Updates Health on Server Side 
  sendHealth();
}

// Looks for event and handles it 
void actionListner()
{

  // Getting Hit (Simulation with Button)
  hitSim.loop();
  
  if (hitSim.isPressed())
  {
    // Decrement by 1 
    health--;
  }

}

// Updates LCD Screen
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
  // Error Handling
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("      Error     ");
  }

}



