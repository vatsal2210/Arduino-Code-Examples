int motorPin1 = 13; 

int state;
int flag=0;        //makes sure that the serial only prints once the state

void setup() {
   
   
    Serial.begin(9600);
}

void loop() {
    //if some date is sent, reads it and saves in state
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }   
    // if the state is '0' the DC motor will turn off
    if (state == '0') {
        digitalWrite(motorPin1, LOW);

        if(flag == 0){
          Serial.println("LED: off");
          flag=1;
        }
    }
    // if the state is '1' the motor will turn right
    else if (state == '1') {
        digitalWrite(motorPin1, HIGH); // set pin 2 on L293D low
        if(flag == 0){
          Serial.println("LED: ON");
          flag=1;
        }
    }
    }

