/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated at least in: 2022-08-25
    @version: 1.0
    @description
        Implements Screen Class
*/

#include <Screen.h>

// PUBLIC METHODS
Screen::Screen() {
}

Screen Screen::operator=(Screen &screen) {
    {
        for (int i = 0; i < MAX_LABELS; i++) {
            labels[i] = screen.labels[i];
        }
        for (int i = 0; i < MAX_BUTTONS; i++) {
            buttons[i] = screen.buttons[i];
        }
        return *this;
    }
}

void Screen::addLabel(uint8_t index, TFTLabel label) {
    if (index < MAX_LABELS) {
        this->labels[index] = label;
    } else {
        Serial.println("Label Index out of bounds, Check MAX_LABELS and function addLabel index argument");
    }
}

void Screen::addButton(uint8_t index, TFTButton button) {
    if (index < MAX_BUTTONS) {
        this->buttons[index] = button;
    } else {
        Serial.println("Button Index out of bounds, Check MAX_BUTTONS and function addLabel index argument");
    }
}

void Screen::draw() {
    for (int i = 0; i < MAX_LABELS; i++) {
        if (!this->labels[i].getIsNull()) {
            this->labels[i].draw();
        }
    }
    for (int i = 0; i < MAX_BUTTONS; i++) {
        if (!this->buttons[i].getIsNull()) {
            this->buttons[i].draw();
        }
    }
}
void Screen::readButtons() {
    for (int i = 0; i < MAX_BUTTONS; i++) {
        if (!this->buttons[i].getIsNull()) {
            if(buttons[i].onPress()){
                Serial.println("Button " + (String)i +" Pressed"); 
                return;
            }
        }
    }
}

Screen::~Screen() {
    
}