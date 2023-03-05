#ifndef pins_stm32_h
#define pins_stm32_h
#include <Arduino.h>

#ifdef SD_MODULE
constexpr uint8_t SD_PIN = 10;
#endif

#ifdef LCD_MODULE
#define USE_STANDARD_LCD
constexpr uint8_t LCD_COLS = 16;
constexpr uint8_t LCD_ROWS = 2;
constexpr uint8_t BuzzerPin = 36;
constexpr uint8_t lcdBackLightPin = 38;
constexpr uint8_t rs = 12;
constexpr uint8_t rw = 13;
constexpr uint8_t en = 11;
constexpr uint8_t d0 = 9;
constexpr uint8_t d1 = 8;
constexpr uint8_t d2 = 7;
constexpr uint8_t d3 = 6;
constexpr uint8_t d4 = 5;
constexpr uint8_t d5 = 4;
constexpr uint8_t d6 = 3;
constexpr uint8_t d7 = 2;
#endif

#ifdef SEVSEG_MODULE
constexpr uint8_t g = 37;
constexpr uint8_t f = 51;
constexpr uint8_t a = 49;
constexpr uint8_t b = 47;
constexpr uint8_t e = 45;
constexpr uint8_t d = 43;
constexpr uint8_t c = 41;
constexpr uint8_t dp = 39;
#endif

#endif //pins_stm32