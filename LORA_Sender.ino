#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

//RTC_DS3231 rtc;
//#define OLED_RESET 9
//Adafruit_SSD1306 display(OLED_RESET);
int counter = 0;

void setup() {
    
   // rtc.adjust(DateTime(2020, 11, 5, 11, 14, 50));
//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  delay(100);
  
//  display.clearDisplay();
//  display.display();
  Serial.begin(9600);
//  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
//   display.clearDisplay();
//  display.setTextSize(1);
//  display.setTextColor(WHITE);  
//  display.setCursor(0,0);
//  DateTime now = rtc.now();
//     display.print(now.hour(), DEC);
//display.print(':');
//  display.setCursor(17,0);
//   display.print(now.minute(), DEC);
//display.print(':');
//  display.setCursor(34,0);
//   display.println(now.second(), DEC);
//
//  display.setCursor(0,17);
//  display.print("Temp: ");
//  display.print(rtc.getTemperature());
//   display.print(" ");
//    display.print((char)247);
//  display.print("C");
//
//  
//  display.display();
//
//
//  // send packet
  LoRa.beginPacket();
 // LoRa.print("hello ");
   LoRa.print("this is pattagobi talking to herself like an idiot.");
   
  LoRa.endPacket();
  delay(1000);
}