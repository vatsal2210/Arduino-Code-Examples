#include <Printers.h>
#include <XBee.h>
#include <SoftwareSerial.h>


unsigned long previousMillis = 0;
const long interval = 4000;
// the interval in mS 
XBee xbee = XBee();
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial soft(2,3);// RX, TX
Rx16Response rx16 = Rx16Response();
ZBRxResponse rx = ZBRxResponse();

XBeeAddress64 addr64 = XBeeAddress64(0x0013a200,0x407a25b5);

char Buffer[128];
char RecBuffer[200];
void setup() {
  // put your setup code here, to run once:
  soft.begin(9600);
  Serial.begin(9600);
  xbee.setSerial(soft);
}
void print8Bits(byte c){
  uint8_t nibble = (c >> 4);
  if (nibble <= 9)
    Serial.write(nibble + 0x30);
  else
    Serial.write(nibble + 0x37);

  nibble = (uint8_t) (c & 0x0F);
  if (nibble <= 9)
    Serial.write(nibble + 0x30);
  else
    Serial.write(nibble + 0x37);
}

void print32Bits(uint32_t dw){
  print16Bits(dw >> 16);
  print16Bits(dw & 0xFFFF);
}

void print16Bits(uint16_t w){
  print8Bits(w >> 8);
  print8Bits(w & 0x00FF);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  xbee.readPacket();
  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
       xbee.getResponse().getZBRxResponse(rx);
       if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED) {
            // the sender got an ACK
            Serial.println("got ACK");
        } else {
            // we got it (obviously) but sender didn't get an ACK
            Serial.println("not got ACK");
        }

        Serial.print("Got an rx packet from: ");
        XBeeAddress64 senderLongAddress = rx.getRemoteAddress64();
        print32Bits(senderLongAddress.getMsb());
        Serial.print(" ");
        print32Bits(senderLongAddress.getLsb());        
        Serial.println(' ');
        
        // this is the actual data you sent
        Serial.println("Received Data: ");
        for (int i = 0; i < rx.getDataLength(); i++) {
          print8Bits(rx.getData()[i]);
          Serial.print(' ');
        }
        
        //Received data as string to serial
        Serial.println(' ');
        Serial.println("In string format");
       for (int i = 0; i < rx.getDataLength(); i++) {
          if (iscntrl(rx.getData()[i]))
            RecBuffer[i] =' ';
          else
            RecBuffer[i]=rx.getData()[i];
        }
        Serial.println(RecBuffer);
        String myString = String((char *)RecBuffer);
        if(myString=="MTON"){
          Serial.println("Switching on Motor");
        }
        else if(myString=="MTOFF"){
          Serial.println("Switching off Motor");
        }
    }
    //clear the char array, other wise data remains in the 
    //buffer and creates unwanted results.
    memset(&RecBuffer[0], 0, sizeof(RecBuffer));
    memset(&Buffer[0], 0, sizeof(Buffer));
  }

  //Send a packet every 4 sec.
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    strcpy(Buffer,"RSLOW");
    uint8_t payload[20]= "RSLOW";

//  ZBTxRequest zbtx = ZBTxRequest(addr64,(uint8_t *)Buffer,sizeof(Buffer));
    ZBTxRequest zbtx = ZBTxRequest(addr64,payload,sizeof(payload));
    xbee.send(zbtx);
  }


}
