#include "wificonfig.h"
#include "reloj.h"

ESP8266WiFiMulti WiFiMulti;

void wifiInit()
{

    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(STASSID, STAPSK);
    unsigned long timeout = millis() + 10000;

    while (WiFi.status() != WL_CONNECTED)
    {
        if (timeout < millis())
        {
            break;
        }
        delay(600);
    }
    if (WiFi.status() == WL_CONNECTED)
    {
    }
    else
    {
    }
}
