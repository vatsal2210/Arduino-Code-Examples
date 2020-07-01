/*
 The circuit:
 *
 * Bluetooth Tx   to  digital pin 0
 * Bluetooth Rx   to  digital pin 1 
 * LCD RS pin     to  digital pin 2
 * LCD Enable pin to  digital pin 3
 * LCD D4 pin     to  digital pin 4
 * LCD D5 pin     to  digital pin 5
 * LCD D6 pin     to  digital pin 6
 * LCD D7 pin     to  digital pin 7
 * LED 1          to  digital pin 8
 * LED 2          to  digital pin 9
 * LED 3          to  digital pin 10
 * Fan 1          to  digital pin 11
 * Fan 2          to  digital pin 12
 * Fan 3          to  digital pin 13
 * LCD R/W pin, LCD (LED-,GND), Blueotooth to ground   
 * LCD (LED+,VCC), Bluetooth 5V            to  5V
*/
 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
#define pwm 11
int led = 2;

//Bluetooth Initialiation
#define bluetoothTx 1   //tx, rx pins for bluetooth module
#define bluetoothRx 0

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
char check;  //char for checking the app response

void setup(void)
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  //Serial.println("Welcome to Tep. Control Device");
  //Serial.println("DEEPS TECHNOLOGY");
  //Serial.println();
  sensors.begin();
  bluetooth.begin(9600);
  
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


void on(){
     analogWrite(pwm, 255);
     lcd.print("Fan Speed: 100%");
     digitalWrite(led, HIGH);
}

void off(){
   analogWrite(10,0);
   lcd.print("    Fan OFF    ");
   digitalWrite(led, LOW);
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
   
  if(temp < 31){
        analogWrite(10,0);
        lcd.print("    Fan Off    ");
//        Serial.print("   Fan Off   ");
        digitalWrite(led, LOW);
        delay(100);
      }
   else if(temp == 31){
        analogWrite(pwm, 75);
        lcd.print("Fan Speed: 20%");
//        Serial.print("Fan Speed: 20%");
        digitalWrite(led, HIGH);
        delay(100);
    } 
   else if(temp == 32){
        analogWrite(pwm, 100);
        lcd.print("Fan Speed: 40%");
//        Serial.print("Fan Speed: 40%");
        digitalWrite(led, HIGH);
        delay(100);
    } 
   else if(temp == 33){
        analogWrite(pwm, 150);
        lcd.print("Fan Speed: 60%");
//        Serial.print("Fan Speed: 60%");
        digitalWrite(led, HIGH);
        delay(100);
    } 
   else if(temp == 34){
        analogWrite(pwm, 200);
        lcd.print("Fan Speed: 80%");
//        Serial.print("Fan Speed: 80%");
        digitalWrite(led, HIGH);
        delay(100);
    } 
  else if(temp > 34){
        analogWrite(pwm, 255);
        lcd.print("Fan Speed: 100%");
//        Serial.print("Fan Speed: 100%");
        digitalWrite(led, HIGH);
        delay(100);
    } 
   
 
   if(bluetooth.available()>= 0)  //checking if bluetooth is connected or not
  {
      Serial.print(sensors.getTempCByIndex(0));
      Serial.print(" C");
      //Serial.println("bluetooth available  ");
      check=bluetooth.read();     //reads char send by bluetooth and stores the in variable check 
      //Serial.println(check);
      if(check=='A')
      {   
          on();  
      }
      if(check=='B')
      {   
          off();    
      }
  }     
}




