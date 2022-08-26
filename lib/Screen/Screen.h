/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated at least in: 2022-08-25
    @version: 1.0
    @description
        Declaration of Screen Class
*/

#include <TFTButton.h>
#include <TFTLabel.h>

#define MAX_LABELS 4   // default 8
#define MAX_BUTTONS 4  // default 7


#pragma once

class Screen {
   private:
    TFTLabel labels[MAX_LABELS];
    TFTButton buttons[MAX_BUTTONS];

   public:
    Screen();

    Screen operator=(Screen &screen);

    void addLabel(uint8_t index, TFTLabel label);
    void addButton(uint8_t index, TFTButton button);
    void draw();
    void readButtons();

    ~Screen();
    };