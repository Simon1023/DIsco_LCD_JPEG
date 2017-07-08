#ifndef MIAT_system
#define MIAT_system

#include "stm32f7xx_hal.h"
//#include "mbed.h"
void SystemClock_Config(void);

#define TRUE 1
#define FALSE 0

#define DEBUG_ENABLE 1
#if(DEBUG_ENABLE == 1)
#define DEBUG(format, args...) printf(format,##args)
#else
#define DEBUG(format, args...)
#endif

#define ERROR(format, args...) printf(format,##args)

#endif
