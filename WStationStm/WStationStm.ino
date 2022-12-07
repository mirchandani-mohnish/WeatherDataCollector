
#include <DHTStable.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25



// pin config 
// bmp sensor
// i2c connnection above AREF 2 pins 
// 
  

#define dht_apin A0 // DHT pin 
#define MQ_apin A1 // MQ sensor Pin 
#define BMP_apin A4 // BMP sensor Pin 
#define uv_apin A3 // UV sensor pin 




Adafruit_BMP085 bmp;
DHTStable DHT;


// variables 
int counter = 0;
int DHTHumVal = 0;
int DHTTemp = 0;
int MQSensorValue = 0;
int pressureVal = 0;
int altitudeVal = 0;
int realAltVal = 0;
int uvVal = 0;
bool LoraFail = false;
float uvSensorVoltage = 0;
float uvIndex = 0;

void setup(){
 
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  
  //Wait before accessing Sensor
  Serial.println("LORA starting...");
  LoRa.begin(433E6);
  
    if (!LoRa.begin(433E6)) {
        Serial.println("Starting LoRa failed!");
        LoraFail = true;

        while(LoraFail){
           LoRa.begin(433E6);
           Serial.println("Reattempting Lora Restart, please check connection");
           if(LoRa.begin(433E6)){
            LoraFail = false;
            break;
           }
        }
    }
    bmp.begin();
     Serial.println("Setup done");
     if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  
  }
 
}
 
void loop(){

    Serial.println("~~~~~New Loop Start~~~~~");
    // DHT Sensor
    DHT.read11(dht_apin);
    
//    Serial.print("Current humidity = ");
//    Serial.print(DHT.getHumidity());
//    Serial.print("%");
//    Serial.print("temperature = ");
//    Serial.print(DHT.getTemperature()); 
//    Serial.println("C  ");
    DHTHumVal = DHT.getHumidity();
    DHTTemp = DHT.getTemperature(); 


    
    // MQ sensor 
    MQSensorValue = analogRead(MQ_apin);       // read analog input pin 0
//    Serial.print("AirQua=");
//    Serial.print(MQSensorValue);               // prints the value read
//    Serial.println(" PPM");
    //delay(2000);//Wait 2 seconds before accessing sensor again.
    


//  bmp 180 
  // pressure value 
//   Serial.print("Pressure = ");
//   Serial.print(bmp.readPressure());
   pressureVal = bmp.readPressure();
//   Serial.println(" Pa");

   // altitude value 
//   Serial.print("Altitude = ");
//   Serial.print(bmp.readAltitude());
   altitudeVal = bmp.readAltitude();
//   Serial.println(" meters");

   // Serial.print("Pressure at sealevel (calculated) = ");
   // Serial.print(bmp.readSealevelPressure());
   // seaLevelPressure
   // Serial.println("Pa");

   // real altitude value 
//   Serial.print("Real altitude = ");
//   Serial.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
   realAltVal = bmp.readAltitude(seaLevelPressure_hPa * 100);
//   Serial.println(" meters");


     // uv value 
     uvVal = analogRead(uv_apin);
    uvSensorVoltage = uvVal/1024*5.0;
//    Serial.print("sensor reading = ");
//    Serial.print(uvVal);
//    Serial.print("        sensor voltage = ");
//    Serial.print(uvSensorVoltage);
//    Serial.println(" V");
////    delay(1000);
//    delay(1000);
//    Serial.println("------------------- end of reading -----------------------");
 Serial.print("00//");
    Serial.print(DHTTemp);
    Serial.print("//");
    Serial.print(DHTHumVal);
    Serial.print("//");
    Serial.print(pressureVal);
    Serial.print("//");
//    Serial.print(altitudeVal);
//    Serial.print("//");
    Serial.print(realAltVal);
    Serial.print("//");
    Serial.print(MQSensorValue);
    Serial.print("//");
    Serial.print(uvIndex);
    Serial.print("//00");
    if(!LoraFail){
      
    // Lora Sender 
    LoRa.beginPacket();
//    LoRa.print("Just something");
    LoRa.print("00//");
    LoRa.print(DHTHumVal);
    LoRa.print("//");
    LoRa.print(DHTTemp);
    LoRa.print("//");
    LoRa.print(MQSensorValue);
    LoRa.print("//");
    LoRa.print(altitudeVal);
    LoRa.print("//");
    LoRa.print(realAltVal);
    LoRa.print("//00");
    LoRa.endPacket();

    Serial.println("Lora packet sent!!!");
    }else{
      Serial.println("Lora packet not sent!!!");
    }
    delay(500);
    Serial.println("Execution Complete -----------------");
}
