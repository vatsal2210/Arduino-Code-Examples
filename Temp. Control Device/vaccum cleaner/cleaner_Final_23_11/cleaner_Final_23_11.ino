/*Version V 1.20
Date: 20/10/2015

Code for interfacing RTC and 20x4 LCD with arduino for vaccum cleaner robot

To display as:

    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
 0 | |I|N|D|U|S| |R|O|B|O|T|I|C| |C|L|U|B| |
 1 | | | | | | |V|S| |B|O|T| |1| | | | | | |
 2 | | | | | |W|E|L|C|O|M|E| |Y|O|U| | | | |
 3 |2|0| |N|O|V|.| | |0|6|:|3|0|:|4|5| |P|M|

by K.P.V.S.Sathvik
*/

#include <Wire.h>
#include <LiquidCrystal.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <SoftwareSerial.h>
#include <SoftPWM.h>

//---------------------------------------------------------------
//LCD Pins
#define Rs_pin  48
#define En_pin  46
#define D4_pin  44
#define D5_pin  42
#define D6_pin  40
#define D7_pin  38
#define Rw_pin  36

// LCD and TIME Initialiation
LiquidCrystal lcd(Rs_pin, En_pin, D4_pin, D5_pin, D6_pin, D7_pin);

tmElements_t tm;  //Object declaration for RTC module

const char *monthName[12] = {
  "Jan.", "Feb.", "Mar.", "Apr.", "May.", "Jun.",
  "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec."
};

//---------------------------------------------------------------
//Motor Pins
#define MOTORA1 7  //Right motor 
#define MOTORA2 6
#define MOTORB1 5   //Left motor
#define MOTORB2 4
#define MOTORC 3  //Vaccum motor
int motorintensity=255;

//Bluetooth Initialiation
#define bluetoothTx 10   //tx, rx pins for bluetooth module
#define bluetoothRx 8

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
char check;  //char for checking the app response
//---------------------------------------------------------------

#define sw  12    //Swicth: Auto/Application

const int sensor_1 = 32;  //IR Sensor
const int sensor_2 = 30;

const int  tPin = 24;   //Ultrasonic Sensor
const int ePin = 26;

double t;   //Time
double d;   //Distance

int sensors[2], i;
byte switch1 = false;

//---------------------------------------------------------------
void setup()
{
  //Serial.begin(9600);

  //LCD Setup
  pinMode(A14, OUTPUT);
  analogWrite(A14, 50);
  lcd.begin (20, 4); // <<-- our LCD is a 20x4, change for your LCD if needed
  digitalWrite(Rw_pin, LOW);

  // Motor and Blu etooth Setup
  pinMode(MOTORA1, OUTPUT);
  pinMode(MOTORA2, OUTPUT);
  pinMode(MOTORB1, OUTPUT);
  pinMode(MOTORB2, OUTPUT);
  pinMode(MOTORC, OUTPUT);
  
  /*SoftPWMBegin();
  SoftPWMSet(MOTORA1, 0);
  SoftPWMSet(MOTORA2, 0);
  SoftPWMSet(MOTORB1, 0);
  SoftPWMSet(MOTORB2, 0);
  SoftPWMSet(MOTORC, 0);*/
  bluetooth.begin(9600);

  pinMode(sensor_1, INPUT);   //IR Sensor i/p Pins
  pinMode(sensor_2, INPUT);
}
//---------------------------------------------------------------

void loop()
{
  // Print our characters on the LCD
  lcd.setCursor(1, 0);  //Start at character 1 on line 0
  lcd.print("INDUS ROBOTIC CLUB");
  lcd.setCursor(6, 1);  //Go to character 6 on line 1
  lcd.print("VS BOT 1");
  lcd.setCursor(5, 2);  //Go to character 5 on line 2
  lcd.print("WELCOME YOU");

  date_time_display();   //Function to display time and Date

  //LDR control
  digitalWrite(14, LOW);
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.print("LDR:");
  Serial.println(sensorValue);

  if (sensorValue < 150)
  {
    Serial.print("LED on");
      digitalWrite(14, HIGH);
  }

  // Motor and Bluetooth/Autonomous Control

  switch1 = false;
  switch1 = digitalRead(sw);
  /*Serial.print("switch:");
  Serial.println(switch1);*/
  if ((tm.Hour == 9) && (tm.Minute >= 0) && (tm.Minute <= 15))
  {
    autonomous();
  }

  if (switch1)  //Switch ON: Autonomous
  {
    Serial.println("Switch ON");
    //stopm();
    autonomous();
  }
  else
  {
    Serial.println("Switch OFF");
    //stopm();
    bluetooth_func();
  }
  //delay(200);
}

//---------------------------------------------------------------
//RTC and LCD Function
void date_time_display()  //Function to display time and Date
{
  if (RTC.read(tm)) //Reads the time from RTC module
  {

    lcd.setCursor(0, 3); //Go to character 0 on line 3
    lcd.print(tm.Day);  //Displays day
    lcd.print(' ');
    int t = tm.Month;
    lcd.print(monthName[t - 1]);

    // Displays time in 12 hours
    print2digits(Hour());  //Displays hour in two digit
    lcd.print(':');
    print2digits(tm.Minute);  //Displays minute in two digit
    lcd.print(':');
    print2digits(tm.Second);  //Displays second in two digit
  }
}

void print2digits(int number)   //Function to display a number in two digits
{
  if (number >= 0 && number < 10)
  {
    lcd.print('0');   //Puts 0 if it is less than 10. For example, if it is 5 than it displays 05
  }
  lcd.print(number);
}

int Hour()  //Funtion to Display time in 12 hours
{
  int h = tm.Hour; //Storing hours from RTC module in h
  lcd.setCursor(18, 3); //Go to character 10 on line 3

  if (h > 12)
  {
    h = h - 12;
    //lcd.setCursor(18, 3);
    lcd.print("PM");  //Display PM if h is greater than 12
  }
  else
  {
    lcd.print("AM");  //Display AM if h is less than 12
  }

  lcd.setCursor(9, 3); //Go to character 10 on line 3
  return h;
}
//---------------------------------------------------------------
// Motor Function
void forward()
{
  //SoftPWMSet(MOTORA1, motorintensity);
  digitalWrite(MOTORA1, HIGH);
  digitalWrite(MOTORA2, LOW);
  //SoftPWMSet(MOTORB1, motorintensity);
  digitalWrite(MOTORB1, HIGH);
  digitalWrite(MOTORB2, LOW);
}

void backward()
{
  digitalWrite(MOTORA1, LOW);
  //SoftPWMSet(MOTORA2, motorintensity);
  digitalWrite(MOTORA2, HIGH);
  digitalWrite(MOTORB1, LOW);
  //SoftPWMSet(MOTORB2, motorintensity);
  digitalWrite(MOTORB2, HIGH);
}

void left()
{
  //SoftPWMSet(MOTORA1, motorintensity);
  digitalWrite(MOTORA1, HIGH);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, LOW);
}

void right()
{
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, LOW);
  //SoftPWMSet(MOTORB1, motorintensity);
  digitalWrite(MOTORB1, HIGH);
  digitalWrite(MOTORB2, LOW);
}

void stopm()
{
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, LOW);
}

void vacuum_on()
{
  digitalWrite(MOTORC, HIGH);
}

void vacuum_off()
{
  digitalWrite(MOTORC, LOW);
}

void autonomous()
{

  sensors[0] = digitalRead(sensor_1);
  sensors[1] = digitalRead(sensor_2);

  Serial.print("IR Sensor:");
  Serial.print(sensors[0]);
  Serial.print(" ");
  Serial.println(sensors[1]);
  
  if (sensors[0] == 1 && sensors[1] == 1 )
  {
    Serial.println("Stop");
    stopm();
  }
  else if (sensors[0] == 0 && sensors[1] == 1 )
  {
    Serial.println("Left");
    left();
  }
  else if (sensors[0] == 1 && sensors[1] == 0 )
  {
    Serial.println("Right");
    right();
  }
  else
  {
    Serial.println("Forward");
    forward();
  }

  //Ultrasonic Sensor: To check Distance
  pinMode(tPin, OUTPUT);
  digitalWrite(tPin, LOW);
  delayMicroseconds(3);
  digitalWrite(tPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin, LOW);
  delayMicroseconds(10);
  pinMode(ePin, INPUT);

  t = pulseIn(ePin, HIGH);
  d = t / 57.1000;

  if (d >= 300 || d <= 0)
  {
    //Serial.print(" Out of range");
  }
  //else
  {
    Serial.print("Ultra Distance:");
    Serial.print(d);
    Serial.println(" cm");
  }
  if (d > 15)
  {
    Serial.print("Ultra Stop");
    stopm();
  }
  //Serial.println("");
  delay(200);
}


void bluetooth_func()
{
  if (bluetooth.available() >= 0) //checking if bluetooth is connected or not
  {
    //Serial.println("bluetooth available  ");
    check = bluetooth.read();   //reads char send by bluetooth and stores the in variable check
    // Serial.println(check);
    if (check == 'U')
    { forward();
      Serial.println(" forward");
    }

    if (check == 'D')
    { backward();
      Serial.println(" backward");
    }

    if (check == 'L')
    { left();
      Serial.println(" left");
    }

    if (check == 'R')
    { right();
      Serial.println(" right");
    }

    if (check == 'S')
    { stopm();
      Serial.println(" stop");
    }

    if (check == '1')
    { vacuum_on();
      Serial.println("  vacuum_on");
    }

    if (check == '0')
    { vacuum_off();
      Serial.println(" vacuum_off");
    }
    delay(200);
  }
}
