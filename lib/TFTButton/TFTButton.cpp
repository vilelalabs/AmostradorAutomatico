/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-08-25
    @version: 1.0
    @description
        implements TFTButton class

*/

#include <TFTButton.h>

// PRIVATE METHODS

void TFTButton::drawPressed() {
    unsigned short bgPressed = BLUE >> 1;
    unsigned short vertexX0 = 0;
    unsigned short vertexY0 = 0;
    unsigned short vertexX1 = 0;
    unsigned short vertexY1 = 0;
    unsigned short vertexX2 = 0;
    unsigned short vertexY2 = 0;

    switch (this->type) {
        case BTN_TYPE_TEXT_GREEN:
            bgPressed = GREEN >> 1;
            break;
        case BTN_TYPE_TEXT_RED:
            bgPressed = DARKRED;
            break;
        default:  // all other types are _BLUE
            bgPressed = BLUE >> 1;
            break;
    }

    switch (this->type) {
        case BTN_TYPE_TEXT_BLUE:
        case BTN_TYPE_TEXT_GREEN:
        case BTN_TYPE_TEXT_RED:
            this->getTFTScreen()->getTFT().fillRect(this->getX(), this->getY(), this->getW(), this->getH(), BLACK);
            this->getTFTScreen()->getTFT().fillRect(this->getX() + 2, this->getY() + 2, this->getW() - 4, this->getH() - 4, GREY);
            this->getTFTScreen()->getTFT().fillRect(this->getX() + 4, this->getY() + 4, this->getW() - 8, this->getH() - 8, bgPressed);
            this->getTFTScreen()->showMsgXY(this->getX() + (this->getW() / 2 - this->getTextWidth() / 2),
                                            this->getY() + (this->getH() / 2 - this->getTextHeight() / 2),
                                            this->getTitle(), GREY);
            break;
        case BTN_TYPE_ARROW_LEFT:
        case BTN_TYPE_ARROW_RIGHT:
        case BTN_TYPE_ARROW_UP:
        case BTN_TYPE_ARROW_DOWN:
            switch (this->type) {
                case BTN_TYPE_ARROW_LEFT:
                    vertexX0 = this->getX() + 12;
                    vertexY0 = this->getY() + this->getH() / 2;
                    vertexX1 = this->getX() + this->getW() / 2 + 12;
                    vertexY1 = this->getY() + 12;
                    vertexX2 = this->getX() + this->getW() / 2 + 12;
                    vertexY2 = this->getY() + this->getH() - 12;
                    break;
                case BTN_TYPE_ARROW_RIGHT:
                    vertexX0 = this->getX() + this->getW() - 12;
                    vertexY0 = this->getY() + this->getH() / 2;
                    vertexX1 = this->getX() + 12;
                    vertexY1 = this->getY() + 12;
                    vertexX2 = this->getX() + 12;
                    vertexY2 = this->getY() + this->getH() - 12;
                    break;
                case BTN_TYPE_ARROW_UP:
                    vertexX0 = this->getX() + this->getW() / 2;
                    vertexY0 = this->getY() + 12;
                    vertexX1 = this->getX() + 12;
                    vertexY1 = this->getY() + this->getH() - 12;
                    vertexX2 = this->getX() + this->getW() - 12;
                    vertexY2 = this->getY() + this->getH() - 12;
                    break;
                case BTN_TYPE_ARROW_DOWN:
                    vertexX0 = this->getX() + this->getW() / 2;
                    vertexY0 = this->getY() + this->getH() - 12;
                    vertexX1 = this->getX() + 12;
                    vertexY1 = this->getY() + 12;
                    vertexX2 = this->getX() + this->getW() - 12;
                    vertexY2 = this->getY() + 12;
                    break;
                default:
                    break;
            }
            this->getTFTScreen()->getTFT().fillRect(this->getX(), this->getY(), this->getW(), this->getH(), BLACK);
            this->getTFTScreen()->getTFT().fillRect(this->getX(), this->getY(), this->getW(), this->getH(), GREY);
            this->getTFTScreen()->getTFT().fillRect(this->getX() + 2, this->getY() + 2, this->getW() - 4, this->getH() - 4, bgPressed);
            this->getTFTScreen()->getTFT().fillTriangle(vertexX0, vertexY0, vertexX1, vertexY1, vertexX2, vertexY2, GREY);

            break;

        case BTN_TYPE_TENTH_PLUS10:
            this->getTFTScreen()->getTFT().fillRect(this->getX(), this->getY(), this->getW(), this->getH(), GREY);
            this->getTFTScreen()->getTFT().fillRect(this->getX() + 2, this->getY() + 2, this->getW() - 4, this->getH() - 4, bgPressed);
            this->getTFTScreen()->showMsgXY(this->getX() + this->getPadding() / 2, this->getY() + this->getPadding() / 2, "+10", GREY);
            break;

        case BTN_TYPE_TENTH_MINUS10:
            this->getTFTScreen()->getTFT().fillRect(this->getX(), this->getY(), this->getW(), this->getH(), GREY);
            this->getTFTScreen()->getTFT().fillRect(this->getX() + 2, this->getY() + 2, this->getW() - 4, this->getH() - 4, bgPressed);
            this->getTFTScreen()->showMsgXY(this->getX() + this->getPadding() / 2, this->getY() + this->getPadding() / 2, "-10", GREY);
            break;
        default:
            break;
    }
}
void TFTButton::drawReleased() {
    unsigned short bgColor = BLUE;
    unsigned short vertexX0 = 0;
    unsigned short vertexY0 = 0;
    unsigned short vertexX1 = 0;
    unsigned short vertexY1 = 0;
    unsigned short vertexX2 = 0;
    unsigned short vertexY2 = 0;

    switch (this->type) {
        case BTN_TYPE_TEXT_BLUE:
            bgColor = BLUE;
            break;
        case BTN_TYPE_TEXT_GREEN:
            bgColor = GREEN;
            break;
        case BTN_TYPE_TEXT_RED:
            bgColor = RED;
            break;
        default:  // all other types are _BLUE
            bgColor = BLUE >> 1;
            break;
    }

    switch (this->type) {
        case BTN_TYPE_TEXT_BLUE:
        case BTN_TYPE_TEXT_GREEN:
        case BTN_TYPE_TEXT_RED:
            this->getTFTScreen()->getTFT().fillRect(this->getX(), this->getY(), this->getW(), this->getH(), WHITE);
            this->getTFTScreen()->getTFT().fillRect(this->getX() + 2, this->getY() + 2, this->getW() - 4, this->getH() - 4, bgColor);
            this->getTFTScreen()->showMsgXY(this->getX() + (this->getW() / 2 - this->getTextWidth() / 2),
                                            this->getY() + (this->getH() / 2 - this->getTextHeight() / 2),
                                            this->getTitle(), WHITE);
            break;
        case BTN_TYPE_ARROW_LEFT:
        case BTN_TYPE_ARROW_RIGHT:
        case BTN_TYPE_ARROW_UP:
        case BTN_TYPE_ARROW_DOWN:
            switch (this->type) {
                case BTN_TYPE_ARROW_LEFT:
                    vertexX0 = this->getX() + 10;
                    vertexY0 = this->getY() + this->getH() / 2;
                    vertexX1 = this->getX() + this->getW() / 2 + 10;
                    vertexY1 = this->getY() + 10;
                    vertexX2 = this->getX() + this->getW() / 2 + 10;
                    vertexY2 = this->getY() + this->getH() - 10;
                    break;
                case BTN_TYPE_ARROW_RIGHT:
                    vertexX0 = this->getX() + this->getW() - 10;
                    vertexY0 = this->getY() + this->getH() / 2;
                    vertexX1 = this->getX() + 10;
                    vertexY1 = this->getY() + 10;
                    vertexX2 = this->getX() + 10;
                    vertexY2 = this->getY() + this->getH() - 10;
                    break;
                case BTN_TYPE_ARROW_UP:
                    vertexX0 = this->getX() + this->getW() / 2;
                    vertexY0 = this->getY() + 10;
                    vertexX1 = this->getX() + 10;
                    vertexY1 = this->getY() + this->getH() - 10;
                    vertexX2 = this->getX() + this->getW() - 10;
                    vertexY2 = this->getY() + this->getH() - 10;
                    break;
                case BTN_TYPE_ARROW_DOWN:
                    vertexX0 = this->getX() + this->getW() / 2;
                    vertexY0 = this->getY() + this->getH() - 10;
                    vertexX1 = this->getX() + 10;
                    vertexY1 = this->getY() + 10;
                    vertexX2 = this->getX() + this->getW() - 10;
                    vertexY2 = this->getY() + 10;
                    break;
                default:
                    break;
            }
            this->getTFTScreen()->getTFT().fillRect(this->getX(), this->getY(), this->getW(), this->getH(), WHITE);
            this->getTFTScreen()->getTFT().fillRect(this->getX() + 2, this->getY() + 2, this->getW() - 4, this->getH() - 4, bgColor);
            this->getTFTScreen()->getTFT().fillTriangle(vertexX0, vertexY0, vertexX1, vertexY1, vertexX2, vertexY2, WHITE);
            break;

        case BTN_TYPE_TENTH_PLUS10:
            this->getTFTScreen()->getTFT().fillRect(this->getX(), this->getY(), this->getW(), this->getH(), WHITE);
            this->getTFTScreen()->getTFT().fillRect(this->getX() + 2, this->getY() + 2, this->getW() - 4, this->getH() - 4, bgColor);
            this->getTFTScreen()->showMsgXY(this->getX() + this->getPadding() / 2, this->getY() + this->getPadding() / 2, "+10", WHITE);
            break;

        case BTN_TYPE_TENTH_MINUS10:
            this->getTFTScreen()->getTFT().fillRect(this->getX(), this->getY(), this->getW(), this->getH(), WHITE);
            this->getTFTScreen()->getTFT().fillRect(this->getX() + 2, this->getY() + 2, this->getW() - 4, this->getH() - 4, bgColor);
            this->getTFTScreen()->showMsgXY(this->getX() + this->getPadding() / 2, this->getY() + this->getPadding() / 2, "-10", WHITE);
            break;

        default:
            break;
    }
}

// PUBLIC METHODS

// otherconstructor implemented on .H file
TFTButton::TFTButton() {}

bool TFTButton::getIsNull() {
    return this->isNull;
}

bool TFTButton::onPress() {
    unsigned long lastTime = millis();
    bool colorChanged = false;
    TSPoint touch = this->getTouch();
    
    if (touch.x > this->getX() && touch.x < this->getX() + this->getW() &&
        touch.y > this->getY() && touch.y < this->getY() + this->getH()) {
        while (millis() < lastTime + BNT_FEEDBACK_TIME) {
            if (!colorChanged) {
                drawPressed();
                colorChanged = true;
            }
        }
        drawReleased();
        this->callback();
        return true;
    }
    return false;
}

void TFTButton::draw() {
    drawReleased();
}

TFTButton::~TFTButton() {
}