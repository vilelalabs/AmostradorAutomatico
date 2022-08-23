#include <Arduino.h>
#include <TFTButton.h>
#include <TFTConfig.h>
#include <TFTLabel.h>
#include <TFTScreen.h>
//#include <Tela.h>

// INICIALIZAÇÕES DA TELA TFT
TFTScreen tft = TFTScreen();

TFTButton btn1 = TFTButton(&tft, 0, SCREEN_H - 70, "AAA", TFTBP_LEFT, TENTH_MINUS10);
TFTButton btn2 = TFTButton(&tft, 100, SCREEN_H - 70, "A", TFTBP_NONE, ARROW_LEFT);
TFTButton btn3 = TFTButton(&tft, SCREEN_W - 150, SCREEN_H - 70, "A", TFTBP_NONE, ARROW_RIGHT);
TFTButton btn4 = TFTButton(&tft, 220, SCREEN_H - 70, "AAA", TFTBP_RIGHT, TENTH_PLUS10);
TFTLabel lbl1 = TFTLabel(&tft, 0, 0, "START", TFTBP_CENTER);

void setup() {
    Serial.begin(9600);
    tft.setup(DRIVER, ROTATION);

    // menu inferior com botões
    //...
    lbl1.draw();

    btn1.draw();
    btn2.draw();
    btn3.draw();
    btn4.draw();
}

unsigned long checkTime = millis();

void loop() {
    // check if TFT buttons is pressed using millis
    if (millis() > checkTime + 250) {
        btn1.onPress([]() {
            Serial.println("-10");
        });
        btn2.onPress([]() {
            Serial.println("<<");
        });
        btn3.onPress([]() {
            Serial.println(">>");
        });
        btn4.onPress([]() {
            Serial.println("+10");
        });
    }
}