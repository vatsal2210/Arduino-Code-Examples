#include <SoftwareSerial.h>
const int pin1 = 8;
const int pin2 = 9; 

//Bluetooth Initialiation
#define bluetoothTx 10   //tx, rx pins for bluetooth module
#define bluetoothRx 12

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
char check;  //char for checking the app response
//---------------------------------------------------------------

void setup()
{
  //Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode (pin1, OUTPUT);
  pinMode (pin2, OUTPUT);
}
//---------------------------------------------------------------

void loop()
{
  if (bluetooth.available() >= 0) //checking if bluetooth is connected or not
  {
    //Serial.println("bluetooth available  ");
    check = bluetooth.read();   //reads char send by bluetooth and stores the in variable check
    // Serial.println(check);
    if (check == "lighton")
    { digitalWrite(8,HIGH);
      //Serial.println(" Light On");
    }

    if (check == "lightoff")
    { digitalWrite(8,LOW);
      //Serial.println(" Light Off");
    }

    if (check == "bulbon")
    {  digitalWrite(9,HIGH);
      //Serial.println(" Bulb On");
    }

    if (check == "bulboff")
    {  digitalWrite(9,LOW);
      //Serial.println(" Bulb off");
    }

    if (check == "stop")
    {     digitalWrite(8,LOW);
          digitalWrite(9,LOW);
      //Serial.println(" Stop");
    }
    //delay(200);
  }
}


