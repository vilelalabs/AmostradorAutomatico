/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-08-21
    @version: 1.0
    @description
        TFT Touch Screen
*/

#pragma once

#include <TFTConfig.h>

class TFTScreen {
   private:
    Adafruit_TFTLCD tft;
    TouchScreen ts = TouchScreen(XP, YP, XM, YM, SENSIBILITY);
    int driver;
    uint8_t rotation;

   protected:
    TSPoint getTouch();

   public:
    TFTScreen();
    Adafruit_TFTLCD getTFT();

    void setup(int driver, uint8_t rotation);
    void showMsgXY(int x, int y, const char *msg, int color);

    ~TFTScreen();
};