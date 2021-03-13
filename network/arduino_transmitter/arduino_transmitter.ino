#include  <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <RF24Network.h>

char msg[6] = "hello";
RF24 radio(7,8);
//const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24Network network(radio);
const uint16_t this_node = 01;
//const uint16_t this_node = 02;
const uint16_t node01 = 00;
struct SensorData {
  float temp;
  float pres;
} Sensor;

void setup(void) {
  Serial.begin(115200);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);
//  radio.setChannel(2);
//  radio.setPayloadSize(7);
//  radio.setDataRate(RF24_250KBPS);
//  radio.openWritingPipe(pipe);
}
void loop(void) {
  Serial.println("send ...");
  //radio.write(msg, 6);
  //delay(3000);
  Sensor.temp = 12.3;
  Sensor.pres = 45.6;
  network.update();
  RF24NetworkHeader header(node01);
  //bool ok = network.write(header, &msg, sizeof(msg));
  bool ok = network.write(header, &Sensor, sizeof(Sensor));
  Serial.println(ok);
  delay(10000);
}
