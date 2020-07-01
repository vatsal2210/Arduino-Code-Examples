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

void setup(void)
{
Serial.begin(9600);
Serial.println("Welcome to TEP !!!");
Serial.println("www.TheEngineeringProjects.com");
Serial.println();
sensors.begin();

lcd.begin(20, 4);
lcd.setCursor(5,0);
lcd.print("Welcome to:");
lcd.setCursor(1,2);
lcd.print("www.TheEngineering");
lcd.setCursor(4,3);
lcd.print("Projects.com");
delay(5000);
}

void loop(void)
{
sensors.requestTemperatures();
Serial.print("Temperature : ");
Serial.println(sensors.getTempCByIndex(0));
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Temperature: ");
lcd.print(sensors.getTempCByIndex(0));
lcd.print("C");
delay(1000);
}
