#ifndef NTP_h
#define NTP_h

#include <Arduino.h>
#include <NTPClient.h>
#include "interface/Time/TimeWrapper.h"

unsigned long PREV_RTC_UPDATE = 0;
// unsigned long RTC_UPDATE_INTERVAL = 86400000;
unsigned long RTC_UPDATE_INTERVAL = 1000;

void UpdateNTP(UDP& _udp, NTPClient* _ntp, TimeWrapper* _rtc) {
    unsigned long currentMillis = millis();
    if (!_ntp->update()) return;
    if ((currentMillis - PREV_RTC_UPDATE < RTC_UPDATE_INTERVAL) ||
        (_ntp->getHours() != 0 && _ntp->getMinutes() != 0 && _ntp->getSeconds() != 0))
        return;

    time_t NTP_TIME = _ntp->getEpochTime();
    time_t RTC_TIME = _rtc->getEpochTime();
    if (NTP_TIME < RTC_TIME) return;
    // _ntp->client_update(_udp);

    PREV_RTC_UPDATE = currentMillis;
    _rtc->setEpochTime(NTP_TIME);
    Serial.println("RTC_UPDATED!");
}

#endif  // NTP