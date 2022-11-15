#include <SPI.h>
#include <LoRa.h>


#define OLED_RESET 9

String LoRaData;
void setup() {
    Serial.begin(9600);
//  while (!Serial);
  Serial.println("LoRa Receiver");
    LoRa.begin(433E6);
    if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
//    while (1){Serial.println("Fail");delay(1000);};
  }
 
}

void loop() {
  
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
       LoRaData = LoRa.readString();
    Serial.print((char)LoRa.read());

    }
         Serial.print(LoRaData); 
     
     Serial.println("");


  }
}