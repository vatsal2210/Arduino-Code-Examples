
#include <SoftwareSerial.h>
#define MOTORA1 2
#define MOTORA2 3
#define MOTORB1 4
#define MOTORB2 5
#define MOTORC1 6
#define MOTORC2 7
/*#define MOTORD1 8
#define MOTORD2 9*/
//#define sw_on_off 11
//#define sw_auto_app 10
#define bluetoothTx 10
#define bluetoothRx 11

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
char check;

byte fw,bw,rt,lt,on_off,auto_app;//application switchs
void setup() 
{
  // put your setup code here, to run once:
  pinMode(MOTORA1,OUTPUT);
  pinMode(MOTORA2,OUTPUT);
  pinMode(MOTORB1,OUTPUT);
  pinMode(MOTORB2,OUTPUT);
  //pinMode(sw_on_off,INPUT);
  //pinMode(sw_auto_app,INPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
  
}

void loop() 
{
  // put your main code here, to run repeatedly:
   /* digitalWrite(MOTORA1,LOW);
    digitalWrite(MOTORA2,LOW);
    digitalWrite(MOTORB1,LOW);
    digitalWrite(MOTORB2,LOW);*/
    
    /*sw1=false;
    sw2=false;
    sw3=false;
    sw4=false;
    on_off=false;*/
    //sw_auto_app=false;
  if(bluetooth.available()>= 2 )
  {
    if(Serial.available())
    {
      check=Serial.read();
      if(check=='U')
      {   fw=true;   }

      if(check=='D')
      {   bw=true;   }
/*
      if(check=='U')
      {   fw=true;   }

      if(check=='U')
      {   fw=true;   }

      if(check=='U')
      {   fw=true;   }*/
    }
  }
    
    //auto_app=digitalRead(sw_auto_app);
    
    if(on_off)
    {
      //if(auto_app)    //if switch is high then manual (bluetooth control) mode
      {
        
        if(fw)
        { forward(); }

        if(bw)
        { backward(); }

        if(lt)
        { left(); }

        if(rt)
        { right(); }
      
      }
      
    }

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
    digitalWrite(MOTORA1,LOW);
    digitalWrite(MOTORA2,HIGH);
}

void motorb_bw()
{
    digitalWrite(MOTORB1,LOW);
    digitalWrite(MOTORB2,HIGH);
}

