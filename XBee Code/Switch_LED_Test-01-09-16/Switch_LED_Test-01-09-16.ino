const int buttonPin = 2;     
const int led =  13; 
int buttonState = 0;

void setup() {
  pinMode (led, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
 
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    setRemoteState(0X5);
    digitalWrite(led, HIGH);
    delay(1000);
  } else {
    setRemoteState(0X4);
    digitalWrite(led, LOW);
    delay(1000);
  }
}

void setRemoteState(char value) {
 
  Serial.write(0X7E);
  Serial.write((byte)0x0);
  Serial.write(0X10);
  Serial.write(0X17);
  Serial.write((byte)0x0);
  Serial.write((byte)0x0);
  Serial.write((byte)0x0);
  Serial.write((byte)0x0);
  Serial.write((byte)0x0);
  Serial.write((byte)0x0);
  Serial.write((byte)0x0);
  Serial.write(0xFF);
  Serial.write(0XFF);
  Serial.write(0XFF);
  Serial.write(0XFE);
  Serial.write(0X02);
  Serial.write('D');
  Serial.write('4');
  Serial.write(value);
  long sum = 0X17 + 0XFF + 0XFF + 0XFF + 0XFE + 0X02 + 'D' + '4' + value;
  Serial.write( 0XFF - (sum & 0XFF)); 
}

  
