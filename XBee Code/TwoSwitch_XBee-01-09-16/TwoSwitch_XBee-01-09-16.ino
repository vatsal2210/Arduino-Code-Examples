const int buttonPin1 = 2;
const int buttonPin2 = 3;     
const int led =  13; 
int buttonState1 = 0;
int buttonState2 = 0;

void setup() {
  pinMode (led, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  Serial.begin(9600);
}

void loop() {
 
  buttonState1 = digitalRead(buttonPin1);
  if (buttonState1 == HIGH) {
    setRemoteState1(0X5);
    digitalWrite(led, HIGH);
    delay(2000);
  } else {
    setRemoteState1(0X4);
    digitalWrite(led, LOW);
    delay(2000);
  }

  buttonState2 = digitalRead(buttonPin2);
  if(buttonState2 == HIGH){
    setRemoteState2(0X5);
    digitalWrite(led, HIGH);
    delay(2000);
    } else {
      setRemoteState2(0X4);
      digitalWrite(led, LOW);
      delay(2000);
      }
}

void setRemoteState1(char value) {
 
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

void setRemoteState2(char value) {
 
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
  Serial.write('7');
  Serial.write(value);
  long sum = 0X17 + 0XFF + 0XFF + 0XFF + 0XFE + 0X02 + 'D' + '7' + value;
  Serial.write( 0XFF - (sum & 0XFF)); 
}
