


#include <TFTLabel.h>
#include <TFTButton.h>

#define MAX_LABELS 7
#define MAX_BUTTONS 7

#pragma once

class Screen{
    private:
     TFTLabel labels[MAX_LABELS];

     TFTButton buttons[MAX_BUTTONS];
    public:
        Screen();
        void addLabel(unsigned short index, TFTLabel label);
        void addButton(unsigned short index, TFTButton button);
        void draw();
        void readButtons();
};