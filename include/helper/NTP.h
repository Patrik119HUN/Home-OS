#ifndef NTP_h
#define NTP_h

#include <Arduino.h>
#include <NTPClient.h>
#include <RTClib.h>

unsigned long PREV_RTC_UPDATE = 0;
// 24 hour interval
// unsigned long RTC_UPDATE_INTERVAL = 86400000;
unsigned long RTC_UPDATE_INTERVAL = 1000;

void UpdateNTP(UDP& _udp, NTPClient* _ntp, RTC_DS3231* _rtc) {
    unsigned long currentMillis = millis();
    if (!_ntp->update()) return;
    if ((currentMillis - PREV_RTC_UPDATE < RTC_UPDATE_INTERVAL) ||
        (_ntp->getHours() != 0 && _ntp->getMinutes() != 0 && _ntp->getSeconds() != 0))
        return;

    DateTime NTP_TIME(
        _ntp->getYear(), _ntp->getMonth(), _ntp->getDay(), _ntp->getHours(), _ntp->getMinutes(),
        _ntp->getSeconds()
    );
    DateTime RTC_TIME = _rtc->now();
    if (NTP_TIME < RTC_TIME) return;
    // _ntp->client_update(_udp);

    PREV_RTC_UPDATE = currentMillis;
    _rtc->adjust(NTP_TIME);
    Serial.println("RTC_UPDATED!");
}

#endif  // NTP