//Version 4
//Date: 10/10/15

#define MOTORFRONTA 2       //2
/*#define MOTORRIGHTA 4       //3
#define MOTORBACKA 6        //4
#define MOTORLEFTA 8        //1
#define MOTORFRONTB 3
#define MOTORRIGHTB 5
#define MOTORBACKB 7
#define MOTORLEFTB 9*/

const int sensor_1 = 50;
/*const int sensor_2 = 48;
const int sensor_3 = 46;
const int sensor_4 = 44;
const int sensor_5 = 42;
const int sensor_6 = 40;
const int sensor_7 = 38;
const int sensor_8 = 36;*/
int sensors[8],i,intensityr=150,intensityl=150,intensity=25,x,count,countl,countr,counts;


void setup() {

  Serial.begin(9600);
 pinMode(sensor_1, INPUT); 
 /*pinMode(sensor_2, INPUT);
 pinMode(sensor_3, INPUT);
 pinMode(sensor_4, INPUT); 
 pinMode(sensor_5, INPUT);
 pinMode(sensor_6, INPUT);
 pinMode(sensor_7, INPUT);*/
 pinMode(MOTORFRONTA, OUTPUT);
/* pinMode(MOTORRIGHTB, OUTPUT);
 pinMode(MOTORLEFTA, OUTPUT);
 pinMode(MOTORLEFTB, OUTPUT);
 pinMode(sensor_8, INPUT);*/

}

void loop() {
  sensors[0] = 0;
 /* sensors[1] = 0;
  sensors[2] = 0;
  sensors[3] = 0;
  sensors[4] = 0;
  sensors[5] = 0;
  sensors[6] = 0;
  sensors[7] = 0;*/

  sensors[0] = digitalRead(sensor_1);
  /*sensors[1] = digitalRead(sensor_2);
  sensors[2] = digitalRead(sensor_3);
  sensors[3] = digitalRead(sensor_4);
  sensors[4] = digitalRead(sensor_5);
  sensors[5] = digitalRead(sensor_6);
  sensors[6] = digitalRead(sensor_7);
  sensors[7] = digitalRead(sensor_8);*/
  /*for ( i = 0; i < 8;i++)
  {
    // sensors[i] = digitalRead(sensor_);
     sensors[i]=!sensors[i];
  }*/
   /*if((sensors[5]==1 || sensors[6]==1 || sensors[7]==1)&&(sensors[0]==0 && sensors[1]==0 && sensors[2]==0 && sensors[3]==0 && sensors[4]==0 ))
  {
    right();
    
  }
  else if((sensors[0]==1 || sensors[1]==1 || sensors[2]==1)&&(sensors[3]==0 && sensors[4]==0 && sensors[5]==0 && sensors[6]==0 && sensors[7]==0 ))
  {
    left();
    
   }
   else if ((sensors[3]==1||sensors[4]==1)&&(sensors[0]==0 && sensors[1]==0 && sensors[2]==0 && sensors[5]==0 && sensors[6]==0 && sensors[7]==0))
  {
    straight();
    
  }*/

  if(sensors[0]==1)
  {
    digitalWrite(MOTORFRONTA, HIGH);
  Serial.print("HIGH");
  }
  else
  {
    digitalWrite(MOTORFRONTA, LOW);
  Serial.print("LOW");
  }
   Serial.println("");
   delay(50);
  
}
/*
 void straight(){
    Serial.print("STRAIGHT");
    analogWrite(MOTORRIGHTA, intensityr);
    analogWrite(MOTORRIGHTB, 0);
    analogWrite(MOTORLEFTA, intensityl);
    analogWrite(MOTORLEFTB, 0);
  }
  
  void left(){
    Serial.print("LEFT");
    /*analogWrite(MOTORRIGHTA, 50);
    analogWrite(MOTORRIGHTB, 0);
    analogWrite(MOTORLEFTA, 50);
    analogWrite(MOTORLEFTB, 0);
    delay(intensity0);
    analogWrite(MOTORRIGHTA, intensity);
    analogWrite(MOTORRIGHTB, 0);
    analogWrite(MOTORLEFTA, intensity);
    analogWrite(MOTORLEFTB, 0);
    analogWrite(MOTORFRONTB, intensity);
    analogWrite(MOTORFRONTA, 0);
    analogWrite(MOTORBACKA, intensity);
    analogWrite(MOTORFRONTB, 0);
    
  }

  void right(){
    Serial.print("RIGHT");
    /*analogWrite(MOTORRIGHTA, 50);
    analogWrite(MOTORRIGHTB, 0);
    analogWrite(MOTORLEFTA, 50);
    analogWrite(MOTORLEFTB, 0);
    delay(intensity0);
    analogWrite(MOTORRIGHTA, intensity);
    analogWrite(MOTORRIGHTB, 0);
    analogWrite(MOTORLEFTA, intensity);
    analogWrite(MOTORLEFTB, 0);
    analogWrite(MOTORFRONTB, intensity);
    analogWrite(MOTORFRONTA, 0);
    analogWrite(MOTORBACKB, intensity);
    analogWrite(MOTORBACKA, 0);
  }
    void rotate(){
      Serial.print("ROTATE");
      analogWrite(MOTORRIGHTA, intensity);
    analogWrite(MOTORRIGHTB, 0);
    analogWrite(MOTORLEFTA, 0);
    analogWrite(MOTORLEFTB, intensity);
    }
    void stopp()
    {
      analogWrite(MOTORRIGHTA, 0);
    analogWrite(MOTORRIGHTB, 0);
    analogWrite(MOTORLEFTA, 0);
    analogWrite(MOTORLEFTB, 0);
    }
    */
