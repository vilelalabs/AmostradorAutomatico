/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-08-25
    @version: 1.0
    @description
        - Declares TFTButton class
        - Generate Buttons for TFTScreen using TFTObject Class

*/

#pragma once

#include <TFTConfig.h>
#include <TFTObject.h>

#define BNT_FEEDBACK_TIME 300

enum BUTTON_TYPE : uint8_t {
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
    
   private:
    bool isNull = true;
    BUTTON_TYPE type;
    void (*callback)();

    void drawPressed();
    void drawReleased();

   public:
    TFTButton();
    TFTButton(TFTScreen *tftScreen, int x, int y, const char *title, TFTObjectPosition position, BUTTON_TYPE type, TFTObjectSize objSize, void (*callback)()) : TFTObject(tftScreen, x, y, title, position, objSize) {
        this->isNull = false;
        this->type = type;
        this->callback = callback;
        // à princípio é necessário um caractere no "title" para que o botão seja renderizado corretamente quando for tipo"ARROW_XXX"
    }
    bool getIsNull();

    bool onPress();
    void draw();

    ~TFTButton();
};