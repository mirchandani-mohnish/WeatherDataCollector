#include <dht.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>




#define seaLevelPressure_hPa 1013.25 // 
#define dht_apin A0 // DHT pin 
#define MQ_apin A1 // MQ sensor Pin 
#define BMP_apin A2 // BMP sensor Pin 



Adafruit_BMP085 bmp;
dht DHT;


// variables 
int counter = 0;
int DHTHumVal;
int DHTTemp;
int MQSensorValue;


void setup(){
 
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  delay(1000);
  //Wait before accessing Sensor
    if (!LoRa.begin(433E6)) {
        Serial.println("Starting LoRa failed!");
    }
}
 
void loop(){
  
    // DHT Sensor
    DHT.read11(dht_apin);
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    DHTHumVal = DHT.humidity;
    DHTTemp = DHT.temperature; 


    
    // MQ sensor 
    MQSensorValue = analogRead(MQ_apin);       // read analog input pin 0
    Serial.print("AirQua=");
    Serial.print(sensorValue, DEC);               // prints the value read
    Serial.println(" PPM");
    delay(2000);//Wait 2 seconds before accessing sensor again.
    


    // bmp 180 
    // pressure value 
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    pressureVal = bmp.readPressure();
    Serial.println(" Pa");

    // altitude value 
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    altitudeVal = bmp.readAltitude();
    Serial.println(" meters");

    // Serial.print("Pressure at sealevel (calculated) = ");
    // Serial.print(bmp.readSealevelPressure());
    // seaLevelPressure
    // Serial.println("Pa");

    // real altitude value 
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
    realAltVal = bmp.readAltitude(seaLevelPressure_hPa * 100);
    Serial.println("meters");



    // uv value 
     uvValue = analogRead(uv_apin);
    sensorVoltage = uvValue/1024*5.0;
    Serial.print("sensor reading = ");
    Serial.print(uvValue);
    Serial.print("        sensor voltage = ");
    Serial.print(sensorVoltage);
    Serial.println(" V");
    delay(1000);


    // Lora Sender 
    LoRa.beginPacket();
    LoRa.print("Packet Begin");
    LoRa.print(DHTHumVal);
    LoRa.print("//");
    LoRa.print(DHTTemp);
    LoRa.print("//");
    LoRa.print(MQSensorValue);
    LoRa.print("//");
    LoRa.print(altitudeVal);
    LoRa.print("//");
    LoRa.print(realAltVal);
    Lora.print("End Packet")
    LoRa.endPacket();
   

}