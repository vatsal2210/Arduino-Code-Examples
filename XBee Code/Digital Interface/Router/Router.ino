int readValue = 0;
void setup() {
  Serial.begin(9600);
}

void loop() {
 if(Serial.available()>21){
  if(Serial.read() == 0X7E){
    for(int i=0; i<19; i++){
      byte discard = Serial.read();
      }
      readValue = Serial.read();
      Serial.print("Motion is:");
      if(readValue == 0){
        Serial.println(" not detected");
       } else if(readValue == 16){ 
           Serial.println("detected");
           }
        }
    }
  }

