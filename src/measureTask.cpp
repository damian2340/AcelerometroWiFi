#include "hardwareConfig.h"
#include "measureTask.h"

SensorAcelerometro sensor;

taskMeasureState_t measureState = ErrorMeasure;
//bufer circular
vectorInt_t measurements[MEASU_BUFFER_SIZE];
unsigned int measuIndex = 0;
unsigned int measuLength = 0;

void measureTask()
{
    static unsigned int count = 0;
    static char str[10];
    switch (measureState)
    {
    case BusyMeasureTemp:
        if (count == 98)
        {
            measureState = BusyMeasureSave;
        }
        count++;
        break;
    case BusyMeasureSave:
        saveMeasure();
        count = 0;
        break;
    case ErrorMeasure:
        break;
    default:;
    }
}

vectorInt_t readFirstMeasure()
{
    int origen = measuIndex - measuLength;
    if (origen >= 0)
    {
        return measurements[origen];
    }
    else
    {
        return measurements[(MEASU_BUFFER_SIZE + measuIndex) - (measuLength)];
    }
}

void eraseFirstMeasure()
{
    measuLength--;
}

void saveMeasure()
{
    vectorInt_t med = sensor.getAcel();
    if (measuLength < MEASU_BUFFER_SIZE - 1)
    {
        if (measuIndex < MEASU_BUFFER_SIZE)
        {
            measurements[measuIndex] = med;
        }
        else
        {
            measurements[0] = med;
        }
        measuIndex++;
        measuLength++;
    }
}

int measuSize()
{
    return measuLength;
}

bool isMeasurenet()
{
    if (measuLength == 0)
        return false;
    return true;
}
