#ifndef __WIFICONFIG_H__
#define __WIFICONFIG_H__

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#ifndef STASSID
#define STASSID "La senalada  2.4"
#define STAPSK "Paunero1947"
#endif

// IPAddress ip(192, 168, 0, 87);
// IPAddress gateway(192, 168, 0, 1);
// IPAddress subnet(255, 255, 255, 0);

void wifiInit();

#endif
