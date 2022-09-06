/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-08-30
    @version: 1.0
    @description
        Implements TFTScreen class
*/

#include <TFTScreen.h>

TFTScreen::TFTScreen() {
    this->tft = MCUFRIEND_kbv(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
}

TFTScreen::~TFTScreen() {
}

void TFTScreen::setup(int driver, uint8_t rotation) {
    this->tft.reset();
    this->tft.begin(driver);
    this->tft.setRotation(rotation);
    this->tft.fillScreen(BLACK);
}

MCUFRIEND_kbv TFTScreen::getTFT() {
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
        outp.x = map(p.y, TS_LEFT, TS_RT, 0, SCREEN_W);
        outp.y = map(p.x, TS_TOP, TS_BOT, 0, SCREEN_H);
        // PORTRAIT MODE
        // outp.x = map(p.x, TS_LEFT, TS_RT, 0, SCREEN_W);
        // outp.y = map(p.y, TS_TOP, TS_BOT, 0, SCREEN_H);

        // DEBUGAR POSIÇÃO DO TOQUE NA TELA
        //  if(outp.z > 0) {
        //      Serial.print("X = ");
        //      Serial.print(outp.x);
        //      Serial.print("\tY = ");
        //      Serial.print(outp.y);
        //      Serial.println();
        //  }
        //--------------------------------

    } else {
        outp.x = outp.y = outp.z = 0;
    }

    // corrige erro na sensibilidade do touch
    if (outp.z == 0) {
        outp.x = outp.y = 0;
    }

    return outp;
}

void TFTScreen::showMsgXY(int x, int y, const char* msg, int color) {
    this->tft.setCursor(x, y);
    this->tft.setTextSize(FONT_SIZE);
    this->tft.setTextColor(color);
    this->tft.println(msg);
}

void TFTScreen::drawPointer(int x, int y) {
    y = y + 15;
    unsigned short vertexX0 = x + 15 ;
    unsigned short vertexY0 = y + 15 / 2;
    unsigned short vertexX1 = x ;
    unsigned short vertexY1 = y ;
    unsigned short vertexX2 = x ;
    unsigned short vertexY2 = y + 15 ;
    this->tft.fillTriangle(vertexX0, vertexY0, vertexX1, vertexY1, vertexX2, vertexY2, TFT_ORANGE);
}