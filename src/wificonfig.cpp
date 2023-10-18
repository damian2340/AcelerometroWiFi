#include "wificonfig.h"
#include "reloj.h"

ESP8266WiFiMulti WiFiMulti;

void wifiInit()
{
    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(STASSID, STAPSK);
    //WiFi.config(ip, gateway, subnet);
    unsigned long timeout = millis() + 10000;
    Serial.print("Esperando conneccion WIFI\n");
    while (WiFi.status() != WL_CONNECTED)
    {
        if (timeout < millis())
        {
            Serial.print("Timeout\n");
            break;
        }
        delay(600);
        Serial.print("wait\n");
        Serial.print((unsigned char)WiFi.status());

    }
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.print("WiFi Conectado\n");
    }
    else
    {
        Serial.print("Problema de Conexion WiFi\n");
    }
    delay(600);
}
