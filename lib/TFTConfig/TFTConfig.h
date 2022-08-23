/*
    @author: Henrique Vilela
    @date: 2022-08-20
    @version: 1.0
    @description
        General configuration for using the TFT Touch Screen

*/

#pragma once

// LIBS
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>

// ARDUINO PINOUT FOR TFT
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

// COLORS
#define WHITE 0xFFFF
#define YELLOW 0xFFE0
#define RED 0xF800
#define DARKRED 0x8800
#define BLUE 0b00000000001111
#define BLACK 0x0000
#define GREEN 0x05C0
#define GREY 0xA630

// TFT TOCHSCREEN  CALIBRATION

#define DRIVER 0x9341

#define XP 8
#define XM A2
#define YP A3
#define YM 9

#define ROTATION 3  // 3 - LANDSCAPE MODE
#define TS_LEFT 893
#define TS_RT 80
#define TS_TOP 113
#define TS_BOT 916

#define SCREEN_W 320
#define SCREEN_H 240

// #define ROTATION 2  // 2 - PORTRAIT MODE -  DONT USE THIS MODE !!!
// #define TS_LEFT 113
// #define TS_RT 916
// #define TS_TOP 80
// #define TS_BOT 893

// #define SCREEN_W 240
// #define SCREEN_H 320

// ADDED CONFIGURATION
#define MINPRESSURE 10
#define MAXPRESSURE 1000
#define SENSIBILITY 300

//------------------------------------------------------------------------------

