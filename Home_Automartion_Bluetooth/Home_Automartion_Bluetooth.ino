#include <SoftwareSerial.h>
const int pin1 = 2;
const int pin2 = 3; 
const int pin3 = 4;

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
  pinMode (pin3, OUTPUT);
}
//---------------------------------------------------------------

void loop()
{
  if (bluetooth.available() >= 0) //checking if bluetooth is connected or not
  {
    //Serial.println("bluetooth available  ");
    check = bluetooth.read();   //reads char send by bluetooth and stores the in variable check
    // Serial.println(check);
    if (check == 'a')
    { digitalWrite(2,HIGH);
      //Serial.println(" Light On");
    }

    if (check == 'b')
    { digitalWrite(2,LOW);
      //Serial.println(" Light Off");
    }

    if (check == 'c')
    {  digitalWrite(3,HIGH);
      //Serial.println(" Bulb On");
    }

    if (check == 'd')
    {  digitalWrite(3,LOW);
      //Serial.println(" Bulb off");
    }
    
     if (check == 'e')
    {  digitalWrite(4,HIGH);
      //Serial.println(" Bulb On");
    }

    if (check == 'f')
    {  digitalWrite(4,LOW);
      //Serial.println(" Bulb off");
    }

    if (check == 's')
    {     digitalWrite(2,LOW);
          digitalWrite(3,LOW);
          digitalWrite(4,LOW);
      //Serial.println(" Stop");
    }
    //delay(200);
  }
}


