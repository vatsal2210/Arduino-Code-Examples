const int led = 13;

void setup() {
  pinMode (led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(led, HIGH);
  setRemoteState(0X5);
  delay(4000);
  digitalWrite(led, LOW);
  setRemoteState(0X4);
  delay(5000);
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

  
