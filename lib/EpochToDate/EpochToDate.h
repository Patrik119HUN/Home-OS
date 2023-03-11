#ifndef EpochToDate_h
#define EpochToDate_h

#include <Arduino.h>

enum day { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
class EpochToDate {
   private:
    time_t _epochTime;
    uint8_t _startingYear;
    day _startingDay;

   public:
    EpochToDate(time_t epochTime, uint8_t startingYear, day startingDay)
        : _epochTime(epochTime), _startingYear(startingYear), _startingDay(startingDay){};
    EpochToDate(time_t epochTime, uint8_t startingYear)
        : EpochToDate(epochTime, startingYear, day::Monday){};
    EpochToDate(time_t epochTime) : EpochToDate(epochTime, 1970, day::Monday){};

    uint16_t getYear() const { return (_epochTime / 31556926L + 1970); }
    uint16_t getMonth() const {
        return (floor((_epochTime % 31556926L) / 2629743L) + _startingDay);
    }
    uint16_t getDay() const {
        return (floor(((_epochTime % 31556926L) % 2629743L) / 86400L) + _startingDay);
    }
    uint16_t getHours() const { return ((_epochTime % 86400L) / 3600); }
    uint16_t getMinutes() const { return ((_epochTime % 3600) / 60); }
    uint16_t getSeconds() const { return (_epochTime % 60); }
};

#endif  // EpochToDate