#include <SoftwareSerial.h>
const int pin1 = 2;
const int pin2 = 3; 
const int pin3 = 4;

//Bluetooth Initialiation
#define bluetoothTx 10   //tx, rx pins for bluetooth module
#define bluetoothRx 12

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
char check;  //char for checking the app response
String readvoice; // check voice
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
    readvoice += check; //build the string
    // Serial.println(check);
  
    if (readvoice.length() > 0) {
      
      if (check == 'a' || readvoice == "Light On")
      { digitalWrite(2,HIGH);
        //Serial.println(" Light On");
      }
  
      if (check == 'b' || readvoice == "Light Off")
      { digitalWrite(2,LOW);
        //Serial.println(" Light Off");
      }
  
      if (check == 'c' || readvoice == "Bulb On")
      {  digitalWrite(3,HIGH);
        //Serial.println(" Bulb On");
      }
  
      if (check == 'd' || readvoice == "Bulb off")
      {  digitalWrite(3,LOW);
        //Serial.println(" Bulb off");
      }
      
      if (check == 'e' || readvoice == " Fan On")
      {  digitalWrite(4,HIGH);
        //Serial.println(" Fan On");
      }
  
     if (check == 'f' || readvoice == "Fan off")
      {  digitalWrite(4,LOW);
        //Serial.println(" Fan off");
      }
  
      if (check == 's' || readvoice == "Stop All")
      {     digitalWrite(2,LOW);
            digitalWrite(3,LOW);
            digitalWrite(4,LOW);
        //Serial.println(" Stop All");
      }
      //delay(200);
  }
  }
} 


