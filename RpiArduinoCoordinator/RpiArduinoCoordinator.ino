#include <XBee.h>
#include <math.h> 
// create the XBee object
XBee xbee = XBee();

int sensor = A5;
uint8_t payload[8] = {0, 0, 0, 0, 0, 0, 0, 0};
// union to convert float to byte string
union u_tag {
    uint8_t b[4];
    float fval;
} u;


// SH + SL Address of receiving XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x40DC7C90);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

int statusLed = 13;
int errorLed = 12;

void flashLed(int pin, int times, int wait) {

  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(wait);
    digitalWrite(pin, LOW);

    if (i + 1 < times) {
      delay(wait);
    }
  }
}

double Thermistor(int RawADC)
{
  double Temp;
  Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  return Temp;
}

void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float rawADC = analogRead(sensor);
  float t = Thermistor (rawADC);

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (!isnan(t)) {

    // convert temperature into a byte array and copy it into the payload array
    u.fval = t;
    for (int i=0;i<4;i++){
      payload[i]=u.b[i];
    }
    u.fval = 100.33;
    for (int i=0;i<4;i++){
      payload[i+4]=u.b[i];
    }

    xbee.send(zbTx);
    flashLed(statusLed, 1, 100);        // flash TX indicator


    // after sending a tx request, we expect a status response, wait up to half second for the status response
    if (xbee.readPacket(500)) {
      // got a response!
      // should be a znet tx status             
      if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
        xbee.getResponse().getZBTxStatusResponse(txStatus);

        // get the delivery status, the fifth byte
        if (txStatus.getDeliveryStatus() == SUCCESS) {
          // success.  time to celebrate
          flashLed(statusLed, 5, 50); 
        } else {
          // the remote XBee did not receive our packet. is it powered on?
          flashLed(errorLed, 3, 500);
        }
      }
    } else if (xbee.getResponse().isError()) {
      //nss.print("Error reading packet.  Error code: ");  
      //nss.println(xbee.getResponse().getErrorCode());
    } else {
      // local XBee did not provide a timely TX Status Response -- should not happen
      flashLed(errorLed, 1, 50);
    }
  }
  delay(2000);
}
