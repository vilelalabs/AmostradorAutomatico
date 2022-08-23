/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-08-21
    @version: 1.0
    @description
        Generate buttons for TFT Button

*/

#pragma once

#include <TFTConfig.h>
#include <TFTObject.h>

enum BUTTON_TYPE {
    TEXT_BLUE,  // "Any text"
    TEXT_GREEN,
    TEXT_RED,
    ARROW_LEFT,  // "Arrows"
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    TENTH_PLUS10,  // "+10", "-10"
    TENTH_MINUS10
};

class TFTButton : public TFTObject {
    //using TFTObject::TFTObject;

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