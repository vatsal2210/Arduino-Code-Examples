/*
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 7
 * LCD D5 pin to digital pin 6
 * LCD D6 pin to digital pin 5
 * LCD D7 pin to digital pin 4
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/
 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

#define ONE_WIRE_BUS 8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
int tempMin = 27;
int tempMax = 36;
int fanSpeed;
int fanLCD;
int fan = 10;             
int led = 2;

void setup(void)
{
  pinMode(fan, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Welcome to TEP !!!");
  Serial.println("DEEPS TECHNOLOGY");
  Serial.println();
  sensors.begin();
  
  lcd.begin(20, 4);
  lcd.setCursor(5,0);
  lcd.print("Welcome to:");
  lcd.setCursor(0,1);
  lcd.print("Temp Control for UPS");
  lcd.setCursor(0,2);
  lcd.print("Made By: Vatsal Shah");
  lcd.setCursor(2,3);
  lcd.print("DEEPS TECHNOLOGY");
  delay(5000);
}

void loop(void)
{
  sensors.requestTemperatures();
  Serial.print("Temperature : ");
  Serial.println(sensors.getTempCByIndex(0));
  int temp = sensors.getTempCByIndex(0);
  Serial.println("Temp is: " + temp);
  if(temp < tempMin) {
      fanSpeed = 0;
      digitalWrite(fan, LOW);
    }
   if((temp >= tempMin) && (temp <= tempMax)) {  // if temperature is higher than minimum temperature
       fanSpeed = map(temp, tempMin, tempMax, 32, 255); 
       fanLCD = map(temp, tempMin, tempMax, 0, 100);  // speed of fan to display on LCD
       analogWrite(fan, fanSpeed);  // spin the fan at the fanSpeed speed
   } 
   if(temp > tempMax) {        // if temp is higher than tempMax
     digitalWrite(led, HIGH);  // turn on led 
   } else {                    // else turn off led
     digitalWrite(led, LOW); 
   }
   
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperature: ");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print(" C");
  lcd.setCursor(3,1);
  lcd.print("Fan Speed: ");
  lcd.print(fanLCD);    // display the fan speed
  lcd.print("%");
  lcd.setCursor(2,3);
  lcd.print("DEEPS TECHNOLOGY");
  delay(200);
}
