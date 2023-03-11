#ifndef pins_stm32_h
#define pins_stm32_h
#include <Arduino.h>

#define SPIWIFI SPI
#define SPIWIFI_SS PA4    // Chip select pin
#define SPIWIFI_ACK PB0   // a.k.a BUSY or READY pin
#define ESP32_RESETN PC1  // Reset pin
#define ESP32_GPIO0 -1    // Not connected

#ifdef SD_MODULE
constexpr uint8_t SD_PIN = PB6;
#endif

#ifdef LCD_MODULE
#define USE_STANDARD_LCD
constexpr uint8_t LCD_COLS = 20;
constexpr uint8_t LCD_ROWS = 4;
constexpr uint8_t BuzzerPin = 36;
constexpr uint8_t lcdBackLightPin = 38;
constexpr uint8_t rs = PC8;
constexpr uint8_t rw = PC6;
constexpr uint8_t en = PC5;
constexpr uint8_t d0 = PA12;
constexpr uint8_t d1 = PA11;
constexpr uint8_t d2 = PB12;
constexpr uint8_t d3 = PB11;
constexpr uint8_t d4 = PB2;
constexpr uint8_t d5 = PB1;
constexpr uint8_t d6 = PB15;
constexpr uint8_t d7 = PB14;
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

#endif  // pins_stm32