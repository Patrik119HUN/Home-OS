#ifndef pins_h
#define pins_h

#ifdef BOARD_DUE
#include "pins_due.h"
#elif BOARD_STM32
#include "pins_stm32.h"
#endif

#endif  // pins