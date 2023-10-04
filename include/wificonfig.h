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

void wifiInit();

#endif
