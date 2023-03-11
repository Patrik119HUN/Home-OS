#ifndef TimeWrapper_h
#define TimeWrapper_h

#include <Arduino.h>

#ifdef ARDUINO_SAM_DUE
#include <RTClib.h>
#elif STM32F0xx
#include <STM32RTC.h>
#endif

class TimeWrapper {
   private:
    STM32RTC* rtc;

   public:
    boolean begin() { rtc->begin(); }

    time_t getEpochTime() { return rtc->getEpoch(); }
    void setEpochTime(time_t time) { rtc->setEpoch(time); }
};
#endif  // Time