/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-08-22
    @version: 1.0
    @description
        Generate buttons for TFT Button

*/

#pragma once

#include <TFTConfig.h>
#include <TFTObject.h>

enum BUTTON_TYPE {
    BTN_TYPE_TEXT_BLUE,  // "Any text"
    BTN_TYPE_TEXT_GREEN,
    BTN_TYPE_TEXT_RED,
    BTN_TYPE_ARROW_LEFT,  // "Arrows"
    BTN_TYPE_ARROW_RIGHT,
    BTN_TYPE_ARROW_UP,
    BTN_TYPE_ARROW_DOWN,
    BTN_TYPE_TENTH_PLUS10,  // "+10", "-10"
    BTN_TYPE_TENTH_MINUS10
};

class TFTButton : public TFTObject {
    // using TFTObject::TFTObject;

   private:
    BUTTON_TYPE type;

    void drawPressed();
    void drawReleased();

   public:
    TFTButton(TFTScreen *tftScreen, int x, int y, const char *title, TFTObjectPosition position, BUTTON_TYPE type) : TFTObject(tftScreen, x, y, title, position) {
        this->type = type;

        // à princípio é necessário um caractere no "title" para que o botão seja renderizado corretamente quando for tipo"ARROW_XXX"
    }
    void onPress(void (*callback)(void));
    void draw();

    ~TFTButton();
};