// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  delay(500);              
  digitalWrite(8, LOW); 
  digitalWrite(9, LOW);// turn the LED off by making the voltage LOW
  delay(500);  
    
}
