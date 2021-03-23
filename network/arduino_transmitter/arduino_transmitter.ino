#include  <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <RF24Network.h>
//===========================================
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>


RF24 radio(7,8);
RF24Network network(radio);
//const uint16_t this_node = 01;
const uint16_t this_node = 02;
const uint16_t node01 = 00;
struct SensorData {
  float temp;
  float pres;
} Sensor;
//===========================================
Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)

void setup(void) {
  Serial.begin(115200);
  SPI.begin();
  if(!bmp.begin(0x76)){ //SE O SENSOR NÃO FOR INICIALIZADO NO ENDEREÇO I2C 0x76, FAZ
    Serial.println(F("Sensor BMP280 não foi identificado! Verifique as conexões."));
    while(1);
  }
  radio.begin();
  network.begin(90, this_node);
}
void loop(void) {
  Serial.println("send ...");
  Sensor.temp = bmp.readTemperature();
  Sensor.pres = bmp.readPressure()*0.01;
  Serial.println(Sensor.temp);
  Serial.println(Sensor.pres);
  Serial.println("sending...");
  network.update();
  RF24NetworkHeader header(node01);
  bool ok = network.write(header, &Sensor, sizeof(Sensor));
  Serial.println(ok);
  delay(10000);
}
