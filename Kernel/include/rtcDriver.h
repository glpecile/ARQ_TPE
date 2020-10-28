/**
 *  header para RTC driver.
 */
#ifndef __RTCDriver_H_
#define __RTCDriver_H_
#include <stdint.h>
#define SECONDS 00
#define MINUTES 02
#define HOURS 04
#define DAY_OF_THE_WEEK 06
#define DAY_OF_THE_MONTH 07
#define MONTH 08
#define YEAR 09
extern uint8_t getRTC(uint64_t descriptor);
uint8_t getTime(int descriptor);
#endif