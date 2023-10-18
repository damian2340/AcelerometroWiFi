#include "Sensor.h"

/*
 * el driver guarda los valores de aceleracion cada vez que se llama a runetime() y se puede acceder a copia de los valores  con getAcel, getRot() y getTemp
*/

void SensorAcelerometro::init()
{
    Wire.begin(4,5);
    Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
    Wire.write(0x6B);                 // PWR_MGMT_1 register
    Wire.write(0);                    // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
}

void SensorAcelerometro::runtime()
{
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);                                // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
    Wire.endTransmission(false);                     // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
    Wire.requestFrom(MPU_ADDR, 7 * 2, true);         // request a total of 7*2=14 registers
    acceleracion.x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
    acceleracion.y = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
    acceleracion.z = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
    temperatura = Wire.read() << 8 | Wire.read();    // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
    giro.x = Wire.read() << 8 | Wire.read();         // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
    giro.y = Wire.read() << 8 | Wire.read();         // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
    giro.z = Wire.read() << 8 | Wire.read();         // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

    updateAcelLfp();
    updateRotLfp();
}

/*
 * retorna un aestructura de 3 int16_t que contiene las aceleraciones en X , Y y Z
*/
vectorInt_t SensorAcelerometro::getAcel() { return acceleracion; }
/*
 * retorna un aestructura de 3 int16_t que contiene las rotaciones en X , Y y Z
*/
vectorInt_t SensorAcelerometro::getRot() { return giro; }

vectorInt_t SensorAcelerometro::getLpfAcel() { return acelLpf; }

vectorInt_t SensorAcelerometro::getLpfRot() { return rotLpf; }
/*
 * retorna un int16_t que contiene temperatura
*/
int16_t SensorAcelerometro::getTemp() { return temperatura; }


void SensorAcelerometro::updateAcelLfp()
{
  acelLpf.x = 7 * (acelLpf.x / 8) + getAcel().x / 8;
  acelLpf.y = 7 * (acelLpf.y / 8) + getAcel().y / 8;
  acelLpf.z = 7 * (acelLpf.z / 8) + getAcel().z / 8;
}

void SensorAcelerometro::updateRotLfp()
{
  rotLpf.x = 7 * (rotLpf.x / 8) + getRot().x / 8;
  rotLpf.y = 7 * (rotLpf.y / 8) + getRot().y / 8;
  rotLpf.z = 7 * (rotLpf.z / 8) + getRot().z / 8;
}
