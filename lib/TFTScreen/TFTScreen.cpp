/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-08-21
    @version: 1.0
    @description
        Implements TFT Touch Screen class
*/

#include <TFTScreen.h>

TFTScreen::TFTScreen() {
    this->tft = Adafruit_TFTLCD(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
}

TFTScreen::~TFTScreen() {
}

void TFTScreen::setup(int driver, uint8_t rotation) {
    this->tft.reset();
    this->tft.begin(driver);
    this->tft.setRotation(rotation);
    this->tft.fillScreen(BLACK);
}

Adafruit_TFTLCD TFTScreen::getTFT() {
    return this->tft;
}

TSPoint TFTScreen::getTouch() {
    TSPoint p;
    TSPoint outp;
    if ((p.z < MINPRESSURE) || (p.z > MAXPRESSURE)) {
        p = this->ts.getPoint();
        outp = p;
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);

        // LANDSCAPE MODE
        outp.x = map(p.y, TS_RT, TS_LEFT, 0, SCREEN_W);
        outp.y = map(p.x, TS_BOT, TS_TOP, 0, SCREEN_H);
        // PORTRAIT MODE
        // p.x = map(p.x, TS_LEFT, TS_RT, 0, SCREEN_W);
        // p.y = map(p.y, TS_TOP, TS_BOT, 0, SCREEN_H);

    } else {
        outp.x = outp.y = outp.z = 0;
    }
    return outp;
}

void TFTScreen::showMsgXY(int x, int y, const char* msg, int color) {
    const int sz = 2;
    this->tft.setCursor(x, y);
    this->tft.setTextSize(sz);
    this->tft.setTextColor(color);
    this->tft.println(msg);
}