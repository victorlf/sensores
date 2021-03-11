#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <RF24Network.h>

char msg[6];
//RF24 radio(12, 14, 26, 25, 27);
RF24 radio(4, 5);
RF24Network network(radio);
//const uint64_t p = 0xE8E8F0F0E1LL;
const uint16_t this_node = 01;
struct SensorData {
  float temp;
  float pres;
} Sensor;

void setup(void){
 Serial.begin(115200);
 SPI.begin();
 radio.begin();
 network.begin(90, this_node);
// radio.setChannel(2);
// radio.setPayloadSize(7);
// radio.setDataRate(RF24_250KBPS);
// radio.openReadingPipe(1,p);
// radio.startListening();
}

void loop(void){
  network.update();
  while (network.available()) {
    RF24NetworkHeader header;
    //unsigned long incomingData;
    char incomingData[6];
    //network.read(header, &incomingData, sizeof(incomingData));
    network.read(header, &Sensor, sizeof(Sensor));
    Serial.print("Temp: ");
    Serial.println(Sensor.temp);
    Serial.print("Pres: ");
    Serial.println(Sensor.pres);
    delay(1000);
  }
// if (radio.available()){  
//     radio.read(msg, 6);      
//     Serial.println(msg);
//     //delay(10);
// }
// else{
//  //Serial.println("No radio available");
// }
}
