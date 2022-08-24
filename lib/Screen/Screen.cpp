

#include <Screen.h>

Screen::Screen() {
}

void Screen::addLabel(unsigned short index, TFTLabel label) {
    if (index < MAX_LABELS) {
        this->labels[index] = label;
    } else {
        Serial.println("Label Index out of bounds");
    }
}

void Screen::addButton(unsigned short index, TFTButton button) {
    if (index < MAX_BUTTONS) {
        this->buttons[index] = button;
    } else {
        Serial.println("Button Index out of bounds");
    }
}

void Screen::draw() {
    for (int i = 0; i < MAX_LABELS; i++) {
        // Serial.print("Label ["+ (String)i +"] :");
        // Serial.println(this->labels[i].getIsNull());

        if (!this->labels[i].getIsNull()) {
            this->labels[i].draw();
        }
    }
    for (int i = 0; i < MAX_BUTTONS; i++) {
        // Serial.print("Button ["+ (String)i +"] :");
        // Serial.println(this->buttons[i].getIsNull());

        if (!this->buttons[i].getIsNull()) {
            this->buttons[i].draw();
        }
    }
}
void Screen::readButtons() {
    for (int i = 0; i < MAX_BUTTONS; i++) {
        if (!this->buttons[i].getIsNull()) {
            buttons[i].onPress();
        }
    }
}