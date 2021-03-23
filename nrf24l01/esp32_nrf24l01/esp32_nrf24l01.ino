#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
//========================
#include <WiFi.h>
#include <HTTPClient.h>

char msg[6];
//RF24 radio(12, 14, 26, 25, 27);
RF24 radio(4, 5);
const uint64_t p = 0xE8E8F0F0E1LL;
//========================
const char* ssid = "Virus";
//const char* ssid = "AndroidAP";
const char* password = "qwertF0ns3c4";
//const char* password = "gaif2892";
String serverName = "http://192.168.0.8:8090/postjson";
//String serverName = "http://159.89.36.81/postjson";
//String serverName = "http://152.84.251.21/postjson";
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

struct SensorData {
  float temp;
  float pres;
} Sensor;

void setup(void){
 Serial.begin(115200);
 radio.begin();
 radio.setChannel(2);
 //radio.setPayloadSize(7);
 radio.enableDynamicPayloads();
 radio.setDataRate(RF24_250KBPS);
 radio.openReadingPipe(1,p);
 radio.startListening();

 WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop(void){
 if (radio.available()){  
     //radio.read(msg, 6);
     //Serial.println(msg);
     Serial.println("reading...");
     radio.read(&Sensor, sizeof(Sensor));      
     Serial.println(Sensor.temp);
     Serial.println(Sensor.pres);
     delay(10);
 }
 else{
  //Serial.println("No radio available");
 }

 //Send an HTTP POST
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverName.c_str());


      // Send HTTP POST request (JSON)
      http.addHeader("Content-Type", "application/json");

      String json;
      json += F("{\"sensor\":\"BMP280\",");
      json += F("\"temperature\":\"");
      json += String(Sensor.temp, 2);
      json += F("\",");
      json += F("\"pressure\":\"");
      json += String(Sensor.pres, 2);
      json += F("\"");
      json += F("}");

      Serial.print(json);

      int httpResponseCode = http.POST(json);
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
