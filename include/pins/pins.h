#ifndef pins_h
#define pins_h

#ifdef ARDUINO_SAM_DUE
#include "pins_due.h"
#elif STM32F0xx
#include "pins_stm32.h"
#endif

#endif  // pins