#ifndef __SENSOR_H__
  #define __SENSOR_H__
  #include "Wire.h"

  #define true true

  typedef struct VECTORINT
  {
      int16_t x;
      int16_t y;
      int16_t z;
  } vectorInt_t;

  class SensorAcelerometro
  {
    public:
      void init(void);
      void runtime(void);
      vectorInt_t getAcel(void);
      vectorInt_t getRot(void);
      vectorInt_t getLpfAcel(void);
      vectorInt_t getLpfRot(void);
      int16_t getTemp(void);

    private:
      const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

      vectorInt_t acceleracion;    // variables for accelerometer raw data
      vectorInt_t giro;            // variables for gyro raw data
      vectorInt_t acelLpf;
      vectorInt_t rotLpf;
      int16_t temperatura;       // variables for temperature data
      
      void updateAcelLfp(void);
      void updateRotLfp(void);
  };

#endif
