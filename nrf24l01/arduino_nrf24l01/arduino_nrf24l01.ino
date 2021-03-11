#include  <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

char msg[6] = "hello";
RF24 radio(7,8);
const uint64_t pipe = 0xE8E8F0F0E1LL;
//===========================================
#include <Adafruit_Sensor.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_BMP280.h> //INCLUSÃO DE BIBLIOTECA
 
Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)

struct SensorData {
  float temp;
  float pres;
} Sensor;

void setup(void) {
  Serial.begin(115200);
  if(!bmp.begin(0x76)){ //SE O SENSOR NÃO FOR INICIALIZADO NO ENDEREÇO I2C 0x76, FAZ
    Serial.println(F("Sensor BMP280 não foi identificado! Verifique as conexões.")); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
  radio.begin();
  radio.setChannel(2);
  //radio.setPayloadSize(7);
  radio.enableDynamicPayloads();
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipe);
}
void loop(void) {
  Sensor.temp = bmp.readTemperature();
  Sensor.pres = bmp.readPressure()*0.01;
  Serial.println(Sensor.temp);
  Serial.println(Sensor.pres);
  Serial.println("sending...");
  //radio.write(msg, 6);
  radio.write(&Sensor, sizeof(Sensor));
  //Serial.println("sending Alt...");
  //radio.write(bmp.readAltitude(1013.25), 10);
  delay(3000);
}
