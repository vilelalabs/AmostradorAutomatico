/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-08-21
    @version: 1.0
    @description
        implements TFTObject class
*/

#include <TFTObject.h>

TFTObject::TFTObject() {}

TFTObject::TFTObject(TFTScreen *tftScreen, int x, int y, const char *title, TFTObjectPosition position, TFTObjectSize objSize) {
    this->tftScreen = tftScreen;
    this->x = x;
    this->y = y;
    this->title = title;
    this->position = position;
    this->objSize = objSize;

    this->padding = 30;
    const uint8_t charWidth = 12;
    const uint8_t charHeight = 20;

    const uint8_t textLength = strlen(this->title);
    this->textWidth = textLength * charWidth;
    this->textHeight = charHeight;

    const unsigned short rectWidth = this->textWidth + padding;
    const unsigned short rectHeight = this->textHeight + padding;

    switch (this->objSize) {
        case OBJ_SIZE_FIXED:
            this->w = FIXED_WIDTH;
            this->h = FIXED_HEIGHT;
            break;
        case OBJ_SIZE_TEXT:
            this->w = rectWidth;
            this->h = rectHeight;
            break;
        default:
            break;
    }

    switch (position) {
        case OBJ_POS_LEFT:
            this->x = 0;
            break;
        case OBJ_POS_RIGHT:
            this->x = SCREEN_W - this->w;
            break;
        case OBJ_POS_CENTER:
            this->x = (SCREEN_W - this->w) / 2;
            break;
        default:
            break;
    }
}

TFTObject TFTObject::operator=(TFTObject tftObject) {
    this->tftScreen = tftObject.tftScreen;
    this->x = tftObject.x;
    this->y = tftObject.y;
    this->title = tftObject.title;
    this->textWidth = tftObject.textWidth;
    this->textHeight = tftObject.textHeight;
    this->position = tftObject.position;
    this->objSize = tftObject.objSize;
    this->padding = tftObject.padding;
    this->w = tftObject.w;
    this->h = tftObject.h;
    return *this;
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
uint8_t TFTObject::getPadding() {
    return this->padding;
}

uint8_t TFTObject::getObjSize() {
    return this->objSize;
}

const char *TFTObject::getTitle() {
    return this->title;
}

uint8_t TFTObject::getTextWidth() {
    return textWidth;
}
uint8_t TFTObject::getTextHeight() {
    return textHeight;
}
TFTObject::~TFTObject() {
}