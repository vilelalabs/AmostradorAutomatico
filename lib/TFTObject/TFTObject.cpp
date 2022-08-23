/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-08-21
    @version: 1.0
    @description
        implements TFTObject class
*/

#include <TFTObject.h>

TFTObject::TFTObject(TFTScreen *tftScreen, int x, int y, const char *title, TFTObjectPosition position) {
    this->tftScreen = tftScreen;
    this->x = x;
    this->y = y;
    this->title = title;
    this->position = position;

    this->padding = 30;
    const unsigned short fontWidth = 18;
    const unsigned short fontHeight = 20;

    const unsigned short textLength = strlen(this->title);
    const unsigned short textWidth = textLength * fontWidth;
    const unsigned short textHeight = fontHeight;
    const unsigned short rectWidth = textWidth + padding;
    const unsigned short rectHeight = textHeight + padding;

    switch (position) {
        case TFTBP_LEFT:
            this->w = rectWidth;
            this->x = 0;
            break;
        case TFTBP_RIGHT:
            this->w = rectWidth;
            this->x = SCREEN_W - this->w;
            break;
        case TFTBP_CENTER:
            this->w = rectWidth;
            this->x = (SCREEN_W - this->w) / 2;
            break;
        default:
            break;
    }

    this->w = rectWidth;
    this->h = rectHeight;
}

void TFTObject::draw() {
    this->tftScreen->getTFT().fillRect(this->x, this->y, this->w, this->h, BLUE);
    this->tftScreen->showMsgXY(this->x + this->padding / 2, this->y + this->padding / 2, this->title, WHITE);
}

TFTScreen *TFTObject::getTFTScreen() {
    return this->tftScreen;
}

int TFTObject::getX() {
    return this->x;
}
int TFTObject::getY() {
    return this->y;
}
int TFTObject::getW() {
    return this->w;
}
int TFTObject::getH() {
    return this->h;
}
int TFTObject::getPadding() {
    return this->padding;
}
const char *TFTObject::getTitle() {
    return this->title;
}
TFTObject::~TFTObject() {
}