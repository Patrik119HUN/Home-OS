#ifndef Log_h
#define Log_h

#include <Arduino.h>
#include <LibPrintf.h>
#ifdef RTC_MODULE
#include <RTClib.h>
#endif
enum LogLevel { DEBUG, ERROR, WARNING, ACK };
class Logger {
   private:
    char Date_Time[27];
    char messageBufferColored[256];
    char messageBuffer[256];

   public:
#ifdef RTC_MODULE
    void println(const char* message, const LogLevel& messageType, DateTime _time) {
        sprintf(
            Date_Time, "%u-%02u-%02uT%02u:%02u:%02u", _time.year(), _time.month(), _time.day(), _time.hour(),
            _time.minute(), _time.second()
        );
        printf("%s[%-*s]", "\e[0;37m", 19, Date_Time);
#else
    void println(const char* message, const LogLevel& messageType) {
#endif
        switch (messageType) {
            case ERROR:
                printf("[%sError%s]:", "\e[0;31m", "\e[0;37m");
                // sprintf(messageBuffer, "[%-*s][Error]:%s", 19, Date_Time, message);
                break;
            case WARNING:
                printf("[%sWarning%s]:", "\e[0;33m", "\e[0;37m");
                // sprintf(messageBuffer, "[%-*s][Warning]:%s", 19, Date_Time, message);
                break;
            case ACK:
                printf("[%sOK%s]:", "\e[0;32m", "\e[0;37m");
                // sprintf(messageBuffer, "[%-*s][OK]:%s", 19, Date_Time, message);
                break;
            case DEBUG:
                printf("[%sDEBUG%s]:", "\e[0;31m", "\e[0;37m");
                // sprintf(messageBuffer, "[%-*s][DEBUG]:%s", 19, Date_Time, message);
                break;
            default:
                break;
        }
        printf("%s\n", message);
    }
};

#endif  // Log