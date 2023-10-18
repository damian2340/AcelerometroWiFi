#include <Arduino.h>
#include "hardwareConfig.h"
#include "sensor.h"
#include "wificonfig.h"
#include "reloj.h"
#include "measureTask.h"

char tmp_str[7]; // temporary variable used in convert function

char stdBufferOut[64];

const char* servidor = "http://co2.df.uba.ar";

extern SensorAcelerometro sensor;
static esp8266::polledTimeout::periodicMs taskPeriod(600);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(NOCEMCU_BAUDRATE);
  Serial.println("arranque!!!");
  sensor.init();

  timeZoneConfig();
  
  wifiInit();
}

void loop() {
  static int indice = 0;
  sensor.runtime();
  delay(2500);

  if (WiFi.status() == WL_CONNECTED){
    Serial.print(sensor.getLpfAcel().x);
    Serial.print(",");
    Serial.print(sensor.getLpfAcel().y);
    Serial.print(",");
    Serial.print(sensor.getLpfAcel().z);
    Serial.println();
    indice++;
  

    WiFiClient client;
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    sprintf(stdBufferOut, "http://co2.df.uba.ar");
    Serial.println(stdBufferOut);
    if (http.begin(client,"http://co2.df.uba.ar")){ // HTTP

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();
      Serial.print("HTTPCODE: ");
      Serial.println(httpCode);
      // httpCode will be negative on error
      if (httpCode > 0){
          // file found at server
          if (httpCode == 200)
          {
              eraseFirstMeasure();
              Serial.println("Recepcion OK");
          }
      }
      else{
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    }
    else
    {
        Serial.printf("[HTTP] Unable to connect\n");
    }
  }
  else
  {
      wifiInit();
      Serial.printf("Desconectado\n");
  }

}

