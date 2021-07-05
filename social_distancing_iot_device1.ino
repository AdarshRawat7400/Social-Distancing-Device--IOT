#include <LiquidCrystal.h>
LiquidCrystal lcd(6,7,2,3,4,5);

int US = 0;
int GREEN_LED = 11;
int RED_LED = 12;
int BUZZER = 13;
int TRIGGER_PIN = 10;
int ECHO_PIN = 9;
int sensorPin = 0;

int safe_distance = 100;


/////////////////////ULTRA SONIC SENSOR//////////////////////////////////

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

//////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
}

void loop()
{
  
  /////////////////TEMPRATURE SENSOR//////////////////////
  int reading = analogRead(sensorPin);
 // measure the 5v with a meter for an accurate value
 //In particular if your Arduino is USB powered
 float voltage = reading * 4.68;
 voltage /= 1024.0;
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100;
  
  ////////////////////////////////////////////////////
  
  
  
  
  /////ULTRASONICS SENSOR + BUZZER + TEMPRATURE SENSOR///////////////////////
  
  US = 0.01723 * readUltrasonicDistance(TRIGGER_PIN, ECHO_PIN);
  delay(100); // Wait for 100 millisecond(s)
  
  
  if (US >= safe_distance || temperatureC < 45) 
  {
    /////////////LCD CODE/////////////////
  	lcd.setCursor(0,0);
  	String line1 = "Temp :- "+(String)temperatureC+"C";
  	lcd.print(line1);
  	lcd.setCursor(0,1);
  	String line2 = "Dist :- "+(String)US+"Cm";
  	lcd.print(line2);
    //////////////////////////////////////
  
    
    digitalWrite(GREEN_LED, HIGH);  // green led on
    digitalWrite(RED_LED, LOW);  // red led off 
    digitalWrite(BUZZER, LOW); // Buzzer OFF

    delay(1000); // Wait for 1000 millisecond(s)
  }
  
  else if(US < safe_distance && temperatureC >= 45)
  {
   	/////////////LCD CODE/////////////////
  	lcd.setCursor(0,0);
  	String line3 = "!!!!!DANGER!!!!!"; 
    lcd.print(line3);
    lcd.setCursor(0,1);
    lcd.print("ISOLATE NOW!!!");

    /////////////////////////////////////
    
    digitalWrite(RED_LED, HIGH); // red led off
    delay(200);         // for blinking
    digitalWrite(RED_LED, LOW);  // red led on
    
	digitalWrite(BUZZER, HIGH); // Buzzer ON
    
    digitalWrite(GREEN_LED, LOW); // green led
    delay(1000); // Wait for 1000 millisecond(s)
  }

///////////////////////////////////////////////////////
	Serial.println(temperatureC);
  


  
}
