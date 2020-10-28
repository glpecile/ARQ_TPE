/**
 * driver para funcionalidad de reloj RTC.
 */ 
#include <rtcDriver.h>

uint8_t getFormat(uint8_t num)
{
    int dec = num & 240;
    dec = dec >> 4;
    int units = num & 15;
    return dec * 10 + units;
}
uint8_t getTime(int descriptor)
{
    uint8_t toReturn = getRTC(descriptor);
    return getFormat(toReturn);
}