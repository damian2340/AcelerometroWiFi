#ifndef __MEASURE_TASK_H__
    #define __MEASURE_TASK_H__
    #include "Sensor.h"

    #define MEASU_BUFFER_SIZE 2110

    typedef enum
    {
        ErrorMeasure = -0x01,
        BusyMeasureSave = 0x04,
        BusyMeasureTemp = 0x08,
    } taskMeasureState_t;

    void measureTask();
    void eraseFirstMeasure();
    void saveMeasure();
    int measuSize();
    bool isMeasurenet();
#endif