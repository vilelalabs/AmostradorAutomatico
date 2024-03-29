/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-08-30
    @version: 1.0
    @description
        Declares TFTScreen class
        Controls screen view and touch events
*/

#pragma once

#include <TFTConfig.h>

class TFTScreen {
   private:
    MCUFRIEND_kbv tft;
    TouchScreen ts = TouchScreen(XP, YP, XM, YM, SENSIBILITY);
    int driver;
    uint8_t rotation;

   protected:
    TSPoint getTouch();

   public:
    TFTScreen();
    MCUFRIEND_kbv getTFT();

    void setup(int driver, uint8_t rotation);
    void showMsgXY(int x, int y, const char *msg, int color);

    void  drawPointer(int x, int y);

    ~TFTScreen();
};