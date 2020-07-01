/*
 Temparature Control Device 
 *
 * Bluetooth Tx   to  digital pin 0
 * Bluetooth Rx   to  digital pin 1 
 * LCD RS pin     to  digital pin 2
 * LCD Enable pin to  digital pin 3
 * LCD D4 pin     to  digital pin 4
 * LCD D5 pin     to  digital pin 5
 * LCD D6 pin     to  digital pin 6
 * LCD D7 pin     to  digital pin 7
 * Temp Sensor    to  digital pin 10
 * Fan 1          to  digital pin 11
 * Fan 2          to  digital pin 12
 * Fan 3          to  digital pin 13
 * LCD R/W pin, LCD (LED-,GND), Blueotooth to ground   
 * LCD (LED+,VCC), Bluetooth 5V            to  5V
 * 
 * Made by: Vatsal Shah
 * Date   : 03-02-17
 * Day    : Friday
*/
 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

//Temp Sensor Initialiation
  #define ONE_WIRE_BUS 10
  OneWire oneWire(ONE_WIRE_BUS);
  DallasTemperature sensors(&oneWire);
//Bluetooth Initialiation
  #define bluetoothTx 1   //tx, rx pins for bluetooth module
  #define bluetoothRx 0
//LCD pins Initialiation
  LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
//Fans Initialiation
  int pwm1 = 11;
  int pwm2 = 12;
  int pwm3 = 13;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
char check;  //char for checking the app response

void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  bluetooth.begin(9600);
  //Serial.println("Welcome to Tep. Control Device");
  //Serial.println("DEEPS TECHNOLOGY");
  //Serial.println();
  
  lcd.begin(20, 4);
  lcd.setCursor(5,0);
  lcd.print("Welcome to:");
  lcd.setCursor(0,1);
  lcd.print("Temp. Control Device");
  lcd.setCursor(0,2);
  lcd.print("Made By: Vatsal Shah");
  lcd.setCursor(2,3);
  lcd.print("DEEPS TECHNOLOGY");
  delay(5000);
}
  
void loop(void)
{
  sensors.requestTemperatures();
  //Serial.print("Temperature : ");
  //Serial.println(sensors.getTempCByIndex(0));
  int temp = sensors.getTempCByIndex(0);
  //Serial.println(temp);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperature: ");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print(" C");
  lcd.setCursor(0,2);
  lcd.print("Made By: Vatsal Shah");
  lcd.setCursor(2,3);
  lcd.print("DEEPS TECHNOLOGY");
  lcd.setCursor(3,1);
   
  if(temp < 30){
       digitalWrite(pwm1,LOW);
       digitalWrite(pwm2,LOW);
       digitalWrite(pwm3,LOW);
        lcd.print("    Fan Off    ");
//        delay(100);
      }
   else if(temp == 30){
       digitalWrite(pwm1,HIGH);
       digitalWrite(pwm2,HIGH);
       digitalWrite(pwm3,HIGH);
        lcd.print("Fan Speed: 20%");
//        delay(100);
    } 
   else if(temp == 31){
        analogWrite(pwm1, 100);
        analogWrite(pwm2, 100);
        analogWrite(pwm3, 100);
        lcd.print("Fan Speed: 40%");
//        delay(100);
    } 
   else if(temp == 32){
        analogWrite(pwm1, 150);
        analogWrite(pwm2, 150);
        analogWrite(pwm3, 150);
        lcd.print("Fan Speed: 60%");
//        delay(100);
    } 
   else if(temp == 34){
        analogWrite(pwm1, 200);
        analogWrite(pwm2, 200);
        analogWrite(pwm3, 200);
        lcd.print("Fan Speed: 80%");
//        delay(100);
    } 
  else if(temp > 34){
        analogWrite(pwm1, 255);
        analogWrite(pwm2, 255);
        analogWrite(pwm3, 255);
        lcd.print("Fan Speed: 100%");
//        delay(100);
    } 
   
 
   if(bluetooth.available()>= 0)  //checking if bluetooth is connected or not
  {
      Serial.print(sensors.getTempCByIndex(0));
      Serial.print(" C");
      //Serial.println("bluetooth available  ");
      check=bluetooth.read();     //reads char send by bluetooth and stores the in variable check 
  }     
}
