/*
    @author: Henrique Vilela
    @created: 2022-08-23
    @updated: 2022-08-23
    @version: 1.0
    @description
        Implements All Screens for TFT Project
*/

#include <Screens.h>

Screen::Screen() {}

void Screen::addLabel(TFTLabel label) {
    TFTLabel *auxLabels = new TFTLabel[labelCount];
    for (unsigned int i = 0; i < labelCount; i++) {
        auxLabels[i] = this->labels[i];
    }
    delete[] this->labels;
    this->labels = new TFTLabel[labelCount + 1];
    for (unsigned int i = 0; i < labelCount; i++) {
        this->labels[i] = auxLabels[i];
    }
    this->labels[labelCount] = label;
    this->labelCount++;
}

void Screen::addButton(TFTButton button) {
    TFTButton *auxButtons = new TFTButton[buttonCount];
    for (unsigned int i = 0; i < buttonCount; i++) {
        auxButtons[i] = this->buttons[i];
    }
    delete[] this->buttons;
    this->buttons = new TFTButton[buttonCount + 1];
    for (unsigned int i = 0; i < buttonCount; i++) {
        this->buttons[i] = auxButtons[i];
    }
    this->buttons[buttonCount] = button;
    this->buttonCount++;
}

void Screen::drawScreen() {

    Serial.println(this->labelCount);
    Serial.println(this->buttonCount);
    // Draw all labels
    for (unsigned short i = 0; i < labelCount; i++) {
        this->labels[i].draw();
        Serial.println("Drawing label");
    }
    // Draw all buttons
    for (unsigned short i = 0; i < buttonCount; i++) {
        this->buttons[i].draw();
        Serial.println("Drawing button");
    }
}
void Screen::readScreenButtons() {
    // Read all buttons
    for (unsigned short i = 0; i < buttonCount; i++) {
        this->buttons[i].onPress();
    }
}

Screen::~Screen() {
    delete[] this->labels;
    delete[] this->buttons;
}