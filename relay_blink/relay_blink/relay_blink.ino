
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() {
 
    pinMode(8, HIGH);
    pinMode(9, HIGH);
    pinMode(10, HIGH);
    pinMode(11, HIGH);
    delay(500);              // wait for a second
    
    pinMode(8, LOW);
    pinMode(9, LOW);
    pinMode(10, LOW);
    pinMode(11, LOW);
    delay(500);              // wait for a second
}
