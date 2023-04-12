// Consants
const double HIT = 1005;

void setup() {
  pinMode(7,INPUT);
  Serial.begin(9600); // open the serial port at 9600 bps:
  // put your setup code here, to run once:

}

// the loop routine runs over and over again forever:
void loop() 
{
  analog();
}


void digital()
{
  if (digitalRead(7) == HIGH)
  {
    Serial.println("Hit Detected!");
  }
}

void analog()
{
  delay(1000);
  
  // read the input on analog pin 0:
  long sensorValue = 0;
  
  // 4.9 is the hit constant in lab envoirnment 
  int count = 0;
  while (true)
  {
    delay(50);
    sensorValue = analogRead(A0);
    Serial.println(count);

    if (sensorValue >= HIT)
    {
      count++;

      if (count > 3)
      {
        Serial.println("Hit Detected!");
        break;
      }
    }
    else
    {
      //Serial.println("No");
    }
  }


}
