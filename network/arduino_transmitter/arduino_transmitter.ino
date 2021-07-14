#include  <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <RF24Network.h>
//===========================================
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
//===========================================
// Adafruit_DHT library will be included
#include "DHT.h"
#define DHTPIN 3
// The sensor will be initialized here
#define DHTTYPE DHT11   // DHT 11
//===========================================
#define ANALOGBATTERY A0
//=============================================



RF24 radio(7,8);
RF24Network network(radio);
const uint16_t this_node = 01;
//const uint16_t this_node = 02;
const uint16_t node01 = 00;
struct SensorData {
  float temp;
  float pres;
  float hum;
  float volt;
} Sensor;
//===========================================
Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)
//===========================================
DHT dht(DHTPIN, DHTTYPE);
//===========================================
// Variables
int analogValue = 0;
float voltage = 0;
float refValue = 5.0 / 1024.0;

void setup(void) {
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  Serial.print("Start setup");
  SPI.begin();
  if(!bmp.begin(0x76)){ //SE O SENSOR NÃO FOR INICIALIZADO NO ENDEREÇO I2C 0x76, FAZ
    Serial.println(F("Sensor BMP280 não foi identificado! Verifique as conexões."));
    while(1);
  }
  dht.begin();
  radio.begin();
  network.begin(90, this_node);
  Serial.print("Finish setup");
}
void loop(void) {
  //digitalWrite(5, LOW);
  digitalWrite(5, HIGH);
  //Serial.println("send ...");
  Sensor.temp = bmp.readTemperature();
  Sensor.pres = bmp.readPressure()*0.01;
  Sensor.hum = dht.readHumidity();
  
  analogValue = analogRead(ANALOGBATTERY);
  Serial.print("Analog Value: ");
  Serial.println(analogValue);
  voltage = refValue * analogValue;
  Sensor.volt = voltage;
  
  Serial.print("Voltage: ");
  Serial.println(voltage);
  Serial.println(Sensor.temp);
  Serial.println(Sensor.pres);
  Serial.print(Sensor.hum);
  Serial.println(" %");
  Serial.println("sending...");
  network.update();
  RF24NetworkHeader header(node01);
  bool ok = network.write(header, &Sensor, sizeof(Sensor));
  Serial.println(ok);
  digitalWrite(5, LOW);
  delay(5000);
}
