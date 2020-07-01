#define sw  8

byte p;

void setup() 
{
  pinMode(sw,INPUT);
  Serial.begin(9600);
}

void loop() 
{
p=digitalRead(sw);  
  if(p)
  {
    Serial.println("Switch pressed");
  }
  else
  {
    Serial.println("Switch not pressed");
  }
  delay(100);
}
