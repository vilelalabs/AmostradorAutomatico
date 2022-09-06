/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated at least in: 2022-08-31
    @version: 1.0
    @description
        Declaration of Screen Class
*/

#include <TFTButton.h>
#include <TFTLabel.h>

#define MAX_LABELS 8   // default minimum 8 
#define MAX_BUTTONS 8  // default minimum 8

#pragma once

class Screen {
   private:
    TFTLabel labels[MAX_LABELS];
    TFTButton buttons[MAX_BUTTONS];
    TFTScreen *tft;

   public:
    Screen();
    Screen(TFTScreen *tft);

    Screen operator=(Screen &screen);

    void addLabel(uint8_t index, TFTLabel label);
    void addButton(uint8_t index, TFTButton button);

    void changeLabel(uint8_t index, char *text);
    void changeButton(uint8_t index, char *text);
    void draw();
    int readButtons();

    TFTLabel getLabel(uint8_t index);

    ~Screen();
};