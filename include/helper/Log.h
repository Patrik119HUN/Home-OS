#ifndef Log_h
#define Log_h

#include <Arduino.h>
#include <EpochToDate.h>
#include <LibPrintf.h>
enum LogLevel { DEBUG, FAULT, WARNING, ACK };
class Logger {
   private:
    char Date_Time[27];
    char messageBufferColored[256];
    char messageBuffer[256];

   public:
#ifdef RTC_MODULE
    void print(const char* message, const LogLevel& messageType, time_t _time) {
        EpochToDate ep(_time);
        sprintf(
            Date_Time, "%u-%02u-%02uT%02u:%02u:%02u", ep.getYear(), ep.getMonth(), ep.getDay(),
            ep.getHours(), ep.getMinutes(), ep.getSeconds()
        );
        printf("%s[%-*s]", "\e[0;37m", 19, Date_Time);
#else
    void println(const char* message, const LogLevel& messageType) {
#endif
        switch (messageType) {
            case FAULT:
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
        printf("%s", message);
    }
    void println(const char* message, const LogLevel& messageType, time_t _time) {
        print(message, messageType, _time);
        printf("\n");
    }
};

#endif  // Log