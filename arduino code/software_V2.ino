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


#include <LiquidCrystal.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// Pin Set up 


// New Constant
const double HIT = 950;

// LCD Set Up
const int rs = 6, en = 7, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Strings to Display
String top = "Soldier 2      ";
String bottom = "Health: ";

int health = 0;
String name = "Soldier 2";
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

  // Debug console
  Serial.begin(9600);

  delay(10);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);
}

void sendHealth()
{
  // Player 1
  //Blynk.virtualWrite(V1,health);
  //Blynk.virtualWrite(V5,score);

  // Player 2
  Blynk.virtualWrite(V9,health);
  Blynk.virtualWrite(V6,score);
}

void loop()
{
  // Death Sequence or Game Over
  if (health == 0)
  {
    delay(2000);
    reset();
  }

  Blynk.run();
  
  // Updates and Displays 
  displayScreen();
  
  // Player 1
  //Blynk.virtualWrite(V2,name);

  // Player 2
  Blynk.virtualWrite(V0,name);
  
  sendHealth();

   // Looks for Hit 
  if (health != 0)
  {
    actionListner();
  }
}

void reset()
{   
  // Display the death screen 
  displayScreen();
  sendHealth();

  // Wait a couple of seconds 
  delay(10000);
  
  // Score Health Reset 
  score = 1000;  
  health = 5;   
}

void actionListner()
{

  // Getting Hit
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
  delay(1000);
  // read the input on analog pin 0:
  long sensorValue;

  // print out the value you read:

  int count = 0;

  while (true)
  {
    delay(50);
    sensorValue = analogRead(A0);
    
    Serial.println(count);
    Serial.println(sensorValue);

    if (sensorValue >= HIT)
    {
      count++;

      if (count > 3)
      {
        Serial.println("Hit Detected!");
        return true;
      }
    }
  }
}
