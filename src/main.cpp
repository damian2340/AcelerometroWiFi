#include <Arduino.h>
#include "acel.h"

char tmp_str[7]; // temporary variable used in convert function

Acelerometer sensor;

vectorInt *acelLfp();
vectorInt *rotLfp();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  sensor.init();
}

void loop() {
  sensor.runtime();
  sensor.runtime();

  /*
  Serial.print(convert_int16_to_str(sensor.getAcel().x));
  Serial.print(",");
  Serial.print(convert_int16_to_str(sensor.getAcel().y));
  Serial.print(",");
  Serial.print(convert_int16_to_str(sensor.getAcel().z));
  */
  /*
  vectorInt rotacion = sensor.getRot();
  Serial.print(convert_int16_to_str(rotacion.x));
  Serial.print(","); 
  Serial.print(convert_int16_to_str(rotacion.y));
  Serial.print(","); 
  Serial.print(convert_int16_to_str(rotacion.z));
  */

  //LPF

  vectorInt *acel = acelLfp();
  Serial.print(acel->x);
  Serial.print(",");
  Serial.print(acel->y);
  Serial.print(",");
  Serial.print(acel->z);
  /*
  vectorInt *rot = rotLfp();
  Serial.print(convert_int16_to_str(rot->x));
  Serial.print(","); 
  Serial.print(convert_int16_to_str(rot->y));
  Serial.print(","); 
  Serial.print(convert_int16_to_str(rot->z));
  */
  Serial.println();
  delay(25);
  
}

vectorInt *acelLfp()
{
  static vectorInt aceleracion;
  aceleracion.x = 7 * (aceleracion.x / 8) + sensor.getAcel().x / 8;
  aceleracion.y = 7 * (aceleracion.y / 8) + sensor.getAcel().y / 8;
  aceleracion.z = 7 * (aceleracion.z / 8) + sensor.getAcel().z / 8;
  return &aceleracion;
}

vectorInt *rotLfp()
{
  static vectorInt rot;
  rot.x = 7 * (rot.x / 8) + sensor.getRot().x / 8;
  rot.y = 7 * (rot.y / 8) + sensor.getRot().y / 8;
  rot.z = 7 * (rot.z / 8) + sensor.getRot().z / 8;
  return &rot;
}
