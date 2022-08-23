/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-08-21
    @version: 1.0
    @description
        implements TFTLabel class

*/

#include <TFTLabel.h>

TFTLabel::TFTLabel() {}

void TFTLabel::draw() {
    unsigned short color = WHITE;

    switch (this->type) {
        case LBL_TYPE_TITLE:
            color = WHITE;
            break;
        case LBL_TYPE_DATA:
            color = YELLOW;
            break;
    }
    this->getTFTScreen()->getTFT().fillRect(this->getX(), this->getY(), this->getW(), this->getH(), BLACK);
    this->getTFTScreen()->showMsgXY(this->getX() + this->getPadding() / 2, this->getY() + this->getPadding() / 2, this->getTitle(), color);
}

TFTLabel::~TFTLabel() {
}