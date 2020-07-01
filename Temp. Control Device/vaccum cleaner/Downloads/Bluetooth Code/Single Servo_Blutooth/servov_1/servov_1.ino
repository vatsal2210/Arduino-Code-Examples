#include <SoftwareSerial.h>

#include <Servo.h> 
Servo myservo1;

int bluetoothTx = 10;
int bluetoothRx = 11;
int ledfade = 13;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  myservo1.attach(9);
  //Setup usb serial connection to computer
  Serial.begin(9600);
  pinMode(ledfade,OUTPUT);
  //Setup Bluetooth serial connection to android
  bluetooth.begin(9600);
}

void loop()
{
  //Read from bluetooth and write to usb serial
  if(bluetooth.available()>= 0 )
  {
    int toSend = bluetooth.read();
    Serial.println(toSend);
    myservo1.write(toSend);
    if(toSend >= 100)
    {
      digitalWrite(ledfade,HIGH);
      digitalWrite(ledfade,LOW);
      delay(100);

    }
    else if(toSend <=50)
     {
       digitalWrite(ledfade,LOW);
     }
   }
   //delay(100);
}

