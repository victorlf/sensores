#include  <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <RF24Network.h>
//===========================================
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
//===========================================
#include "LowPower.h"
//===========================================
#define ANALOGBATTERY A0
#define SENSORSPOWER 5


RF24 radio(7,8);
RF24Network network(radio);
const uint16_t this_node = 01;
//const uint16_t this_node = 02;
const uint16_t node01 = 00;
struct SensorData {
  float temp;
  float pres;
  float volt;
} Sensor;
//===========================================
Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)
//===========================================
// Variables
int analogValue = 0;
float voltage = 0;
float refValue = 5.0 / 1024.0;

void bmp_setup() {
  if(!bmp.begin(0x76)){ //SE O SENSOR NÃO FOR INICIALIZADO NO ENDEREÇO I2C 0x76, FAZ
    Serial.println(F("Sensor BMP280 não foi identificado! Verifique as conexões."));
    while(1);
  }
}

void nrf_setup() {
  radio.begin();
  network.begin(90, this_node);
}

void setup() {
  Serial.begin(115200);
  SPI.begin();
  Serial.print("dsdsd");
  
  // Init sensors Power Supply
  pinMode(SENSORSPOWER, OUTPUT);
  //digitalWrite(SENSORSPOWER, HIGH);
  //delay(1000);
}
void loop() {
  digitalWrite(SENSORSPOWER, LOW);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  
  digitalWrite(SENSORSPOWER, HIGH);
  delay(1000);
  bmp_setup();
  nrf_setup();
  
  //Serial.println("send ...");
  Sensor.temp = bmp.readTemperature();
  Sensor.pres = bmp.readPressure()*0.01;
  
  analogValue = analogRead(ANALOGBATTERY);
  Serial.print("Analog Value: ");
  Serial.println(analogValue);
  voltage = refValue * analogValue;
  Sensor.volt = voltage;
  
  Serial.print("Voltage: ");
  Serial.println(voltage);
  Serial.println(Sensor.temp);
  Serial.println(Sensor.pres);
  Serial.println("sending...");
  network.update();
  RF24NetworkHeader header(node01);
  bool ok = network.write(header, &Sensor, sizeof(Sensor));
  Serial.println(ok);
  //delay(10000);
  
  // End sensors Power Supply
//  digitalWrite(SENSORSPOWER, LOW);
}
