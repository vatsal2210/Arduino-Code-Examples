/*
  Two Bulb Test
  Bulb 1 : Pin 10
  Bulb 2 : Pin 13
 */

void setup() {
  pinMode(10,OUTPUT);
  pinMode(13, OUTPUT);
}


void loop() {
    /* Bulb 1*/
  digitalWrite(10,HIGH);
  delay(800);
  digitalWrite(10,LOW);
  delay(1500);
  /* Bulb 2*/
  digitalWrite(13, HIGH); 
  delay(800);              
  digitalWrite(13, LOW);    
  delay(1200);              
}
