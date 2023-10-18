#include "reloj.h"
#include "C:\Users\damia\.platformio\packages\framework-arduinoespressif8266\cores\esp8266\time.cpp"

//#define TZ_STRING TZ_America_Argentina_Buenos_Aires

const char *TZstr = "PSTR(\"<03>-3\")";
const char *server1 = "pool.ntp.org";

extern "C" int clock_gettime(clockid_t unused, struct timespec *tp);

//time_t now;

uint32_t sntp_startup_delay_MS_rfc_not_less_than_60000()
{
    //info_sntp_startup_delay_MS_rfc_not_less_than_60000_has_been_called = true;
    return 25000; // 25s (or lwIP's original default: (random() % 5000))
}

uint32_t sntp_update_delay_MS_rfc_not_less_than_15000()
{
    //info_sntp_update_delay_MS_rfc_not_less_than_15000_has_been_called = true;
    return 15000; // 15s
}

void timeZoneConfig()
{
    configTime(TZstr, server1, server1, server1);
}

time_t timeNow()
{
    return time(nullptr);
}

void timeFormat4y2M2d2h2m2s(time_t valorFecha, char *fechaDeSalida)
{
    // formato yyyyMMddhhmmss
    const tm *tmData = localtime(&valorFecha);
    sprintf(fechaDeSalida, "%4d%02d%02d%02d%02d%02d", (tmData->tm_year) + 1900, (tmData->tm_mon) + 1, tmData->tm_mday, tmData->tm_hour, tmData->tm_min, tmData->tm_sec);
}
