/*Version V 1.20
Date: 14/10/2015

Code for bluetooth app interface with arduino for vaccum cleaner robot

by K.P.V.S.Sathvik

*/

#include <Wire.h>
#include <LiquidCrystal.h>
#include <Time.h>
#include <DS1307RTC.h> 

#define Rs_pin  0
#define En_pin  2
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
#define Rw_pin  8
//#define BACKLIGHT_PIN 3

LiquidCrystal lcd(Rs_pin,En_pin,D4_pin,D5_pin,D6_pin,D7_pin);

tmElements_t tm;  //Object declaration for RTC module


#define tPin_f  22  //trigger pin
#define ePin_f  24  //echo pin
#define tPin_r  26
#define ePin_r  28
#define tPin_l  30
#define ePin_l  32
/*#define m1_a  5  //left motor
#define m1_b  4 
#define m2_a  3  //right motor
#define m2_b  2*/
int d_f, d_r, d_l ;  //time and distance for front, right, left sensors
float t_f, t_r, t_l;



#include <SoftwareSerial.h>

#define MOTORA1 9  //Right motor 
#define MOTORA2 10
#define MOTORB1 40   //Left motor
#define MOTORB2 42
#define MOTORC 1  //Vaccum motor


#define bluetoothTx 11   //tx, rx pins for bluetooth module
#define bluetoothRx 12

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

char check;  //char for checking the app response


#define buttonPin  52     // the number of the pushbutton pin
//const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status


//byte fw,bw,rt,lt,on_off,auto_app;//application switchs
void setup() 
{
  pinMode(MOTORA1,OUTPUT);
  pinMode(MOTORA2,OUTPUT);
  pinMode(MOTORB1,OUTPUT);
  pinMode(MOTORB2,OUTPUT);
  pinMode(MOTORC,OUTPUT);
  //pinMode(MOTORC2,OUTPUT); 
 
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(A8,OUTPUT);
  analogWrite(A8,50);
  lcd.begin (20,4); // <<-- our LCD is a 20x4, change for your LCD if needed
  digitalWrite(Rw_pin,LOW);

pinMode(tPin_f, OUTPUT);
  pinMode(ePin_f,INPUT);
  pinMode(tPin_r, OUTPUT);
  pinMode(ePin_r,INPUT);
  pinMode(tPin_l, OUTPUT);
  pinMode(ePin_l,INPUT);
 /* pinMode(m1_a, OUTPUT);
  pinMode(m1_b, OUTPUT);
  pinMode(m2_a, OUTPUT);
  pinMode(m2_b, OUTPUT); */ 

pinMode(buttonPin, INPUT);
}

void loop() 
{
  lcd.setCursor(1,0);   //Start at character 1 on line 0
  lcd.print("INDUS ROBOTIC CLUB");
  lcd.setCursor(6,1);   //Go to character 6 on line 1
  lcd.print("VS BOT 1");
  lcd.setCursor(5,2);   //Go to character 5 on line 2
  lcd.print("WELCOME YOU");

  date_time_display();   //Function to display time and Date
  
  //delay(500);

buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) 
  {
    Serial.println("Switch pressed");
    if(bluetooth.available()>= 0)  //checking if bluetooth is connected or not
    {
      Serial.print("bluetooth available  ");
      check=bluetooth.read();     //reads char send by bluetooth and stores the in variable check 
     // Serial.println(check);
      if(check=='U')
      {   forward();   
          Serial.println(" forward");   }

      if(check=='D')
      {   backward();   
          Serial.println(" backward");   }

      if(check=='L')
      {   left();   
          Serial.println(" left");   }

      if(check=='R')
      {   right();   
          Serial.println(" right");   }

      if(check=='S')
      {   stopm();   
          Serial.println(" stop");   }

      if(check=='1')
      {   vacuum_on();   
          Serial.println("  vacuum_on");   }

      if(check=='0')
      {   vacuum_off();   
          Serial.println(" vacuum_off");   }
      delay(200);
      }
    } 
    
    else 
    {
      Serial.println("Switch NOT pressed");
        digitalWrite(tPin_f, LOW);
        delayMicroseconds(3);
        digitalWrite(tPin_f, HIGH);
        delayMicroseconds(10);
        digitalWrite(tPin_f, LOW);
        delayMicroseconds(10);
        pinMode(ePin_f, INPUT);
        t_f = pulseIn(ePin_f, HIGH);
        d_f = (t_f * 34 * 3)/5800;

        digitalWrite(tPin_r, LOW);
        delayMicroseconds(3);
        digitalWrite(tPin_r, HIGH);
        delayMicroseconds(10);
        digitalWrite(tPin_r, LOW);
        delayMicroseconds(10);
        pinMode(ePin_r, INPUT);
        t_r = pulseIn(ePin_r, HIGH);
        d_r = (t_r * 34 * 3)/5800;
      
        digitalWrite(tPin_l, LOW);
        delayMicroseconds(3);
        digitalWrite(tPin_l, HIGH);
        delayMicroseconds(10);
        digitalWrite(tPin_l, LOW);
        delayMicroseconds(10);
        pinMode(ePin_l, INPUT);
        t_l = pulseIn(ePin_l, HIGH);
        d_l = (t_l * 34 * 3)/5800;
        
      
        
        /*if (d >= 200 || d <= 0)
          {
            Serial.println("Out of range");
          }*/
          //else 
          {
            Serial.print(d_f);
            Serial.println("f_cm  ");
            Serial.print(d_r);
            Serial.println("r_cm  ");
            Serial.print(d_l);
            Serial.println("l_cm  ");
            Serial.println("  ");
          }
          
          /*if (d_f < 20)
          {
            
            reverse();
            delay(1000);
            if(d_r<20)
            {  left_turn();}
            else if(d_l<20)
            {   right_turn();}
            else
            { reverse();
              delay(3000); 
            }
          }
           else
          {
            forward();
            Serial.print("forward");
          }*/
      
          delay(200);

    
    }     
}


/*
void forward()
{
digitalWrite(MOTORA1, HIGH);
digitalWrite(MOTORA2, LOW);
digitalWrite(MOTORB1, HIGH);
digitalWrite(MOTORB2, LOW);
}

void reverse()
{
digitalWrite(MOTORA1, LOW);
digitalWrite(MOTORA2, HIGH);
digitalWrite(MOTORB1, LOW);
digitalWrite(MOTORB2, HIGH);
}

void right_turn()
{
digitalWrite(MOTORA1, HIGH);
digitalWrite(MOTORA2, LOW);
digitalWrite(MOTORB1, LOW);
digitalWrite(MOTORB2, LOW);
delay(2000);
}

void left_turn()
{
digitalWrite(MOTORA1, LOW);
digitalWrite(MOTORA2, LOW);
digitalWrite(MOTORB1, HIGH);
digitalWrite(MOTORB2, LOW);
delay(2000);
}  
*/


void date_time_display()  //Function to display time and Date
{
  if (RTC.read(tm)) //Reads the time from RTC module
  {
    
    lcd.setCursor(0,3); //Go to character 0 on line 3
    lcd.print(tm.Day);  //Displays day
    lcd.print('.');
    lcd.print(tm.Month); //Displays month
    lcd.print('.');
    lcd.print(tmYearToCalendar(tm.Year));   //Displays year in two digits

    // Displays time in 12 hours
    lcd.setCursor(10,3); //Go to character 10 on line 3
    print2digits(Hour());  //Displays hour in two digit
    lcd.print(':');
    print2digits(tm.Minute);  //Displays minute in two digit
    lcd.print(':');
    print2digits(tm.Second);  //Displays second in two digit

    /*
    // Displays time in 24 hours  
    lcd.setCursor(12,3); //Go to character 12 on line 3
    print2digits(tm.Hour());  //Displays hour in two digit
    lcd.print(':');
    print2digits(tm.Minute);  //Displays minute in two digit
    lcd.print(':');
    print2digits(tm.Second);  //Displays second in two digit
    */
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
  int h=tm.Hour;  //Storing hours from RTC module in h
  lcd.setCursor(18,3); //Go to character 10 on line 3
  
  if(h>12)
  {
    h=h-12;
    lcd.print("PM");  //Display PM if h is greater than 12
  }
  else
  {
    lcd.print("AM");  //Display AM if h is less than 12
  }

  lcd.setCursor(10,3); //Go to character 10 on line 3
  
  return h;
}


void forward()
{
    digitalWrite(MOTORA1,HIGH);
    digitalWrite(MOTORA2,LOW);
    digitalWrite(MOTORB1,HIGH);
    digitalWrite(MOTORB2,LOW);
}

void backward()
{
    digitalWrite(MOTORA1,LOW);
    digitalWrite(MOTORA2,HIGH);
    digitalWrite(MOTORB1,LOW);
    digitalWrite(MOTORB2,HIGH);
}

void left()
{
    digitalWrite(MOTORA1,HIGH);
    digitalWrite(MOTORA2,LOW);
    digitalWrite(MOTORB1,LOW);
    digitalWrite(MOTORB2,LOW);
}

void right()
{
    digitalWrite(MOTORA1,LOW);
    digitalWrite(MOTORA2,LOW);
    digitalWrite(MOTORB1,HIGH);
    digitalWrite(MOTORB2,LOW);
}

void stopm()
{
    digitalWrite(MOTORA1,LOW);
    digitalWrite(MOTORA2,LOW);
    digitalWrite(MOTORB1,LOW);
    digitalWrite(MOTORB2,LOW);
}

void vacuum_on()
{
    digitalWrite(MOTORC,HIGH);
}

void vacuum_off()
{
    digitalWrite(MOTORC,LOW);
}
