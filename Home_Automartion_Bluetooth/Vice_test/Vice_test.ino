#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11); //TX, RX respetively
String device;

void setup() {

  BT.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); 
  }

//-----------------------------------------------------------------------//

void loop() {

  while (BT.available()){ //Check if there is an available byte to read
    delay(10); //Delay added to make thing stable
    char c = BT.read(); //Conduct a serial read
    device += c; //build the string.
    }
  
  if (device.length() > 0) {

    if(device == "light on") {

      digitalWrite(3, HIGH); }

  else if(device == "light off") {

    digitalWrite(3, LOW); }

  else if (device == "bulb on") {

    digitalWrite (4,HIGH); }

  else if ( device == "bulb off") {

    digitalWrite (4, LOW); }

  else if (device == "fab on") {

    digitalWrite (5, HIGH); }

  else if (device == "fan off") {

    digitalWrite (5, LOW);}

device="";}} //Reset the variable
