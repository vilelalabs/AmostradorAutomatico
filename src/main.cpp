#include <Arduino.h>
#include <TFTButton.h>
#include <TFTConfig.h>
#include <TFTLabel.h>
#include <TFTScreen.h>
#include <Screens.h>
//#include <Tela.h>

// INICIALIZAÇÕES DA TELA TFT
TFTScreen tft = TFTScreen();

Screen *telaTempoCiclos = new Screen();

// // Voltar para a tela inicial
// TFTButton btnVoltar = TFTButton(&tft, 0, 0, "A", TFTBP_LEFT, BTN_TYPE_ARROW_LEFT);

// // Title
// TFTLabel lblTitle = TFTLabel(&tft, 0, 0, "Menu - Tal", TFTBP_CENTER, LBL_TYPE_TITLE);

// TFTLabel lblItem1 = TFTLabel(&tft, 60, 55, "ITEM 1:", TFTBP_NONE, LBL_TYPE_TITLE);
// TFTLabel lblItem2 = TFTLabel(&tft, 60, 90, "ITEM 2:", TFTBP_NONE, LBL_TYPE_TITLE);
// TFTLabel lblItem3 = TFTLabel(&tft, 60, 125, "ITEM 3:", TFTBP_NONE, LBL_TYPE_TITLE);
// TFTLabel lblItem4 = TFTLabel(&tft, lblItem1.getX() + lblItem1.getW(), 55, "00x", TFTBP_NONE, LBL_TYPE_DATA);
// TFTLabel lblItem5 = TFTLabel(&tft, lblItem2.getX() + lblItem2.getW(), 90, "11x", TFTBP_NONE, LBL_TYPE_DATA);
// TFTLabel lblItem6 = TFTLabel(&tft, lblItem3.getX() + lblItem3.getW(), 125, "22x", TFTBP_NONE, LBL_TYPE_DATA);

// // Options

// TFTButton btnUp = TFTButton(&tft, 0, 45, "A", TFTBP_RIGHT, BTN_TYPE_ARROW_UP);
// TFTButton btnDown = TFTButton(&tft, 0, 105, "A", TFTBP_RIGHT, BTN_TYPE_ARROW_DOWN);

// // Navigation
// TFTButton btnMinus10 = TFTButton(&tft, 0, SCREEN_H - 50, "AAA", TFTBP_LEFT, BTN_TYPE_TENTH_MINUS10);
// TFTButton btnMinus1 = TFTButton(&tft, 100, SCREEN_H - 50, "A", TFTBP_NONE, BTN_TYPE_ARROW_LEFT);
// TFTButton btnPlus1 = TFTButton(&tft, SCREEN_W - 150, SCREEN_H - 50, "A", TFTBP_NONE, BTN_TYPE_ARROW_RIGHT);
// TFTButton btnPlus10 = TFTButton(&tft, 220, SCREEN_H - 50, "AAA", TFTBP_RIGHT, BTN_TYPE_TENTH_PLUS10);
void setup() {
    Serial.begin(9600);
    tft.setup(DRIVER, ROTATION);

    telaTempoCiclos->addLabel(TFTLabel(&tft, 60, 35, "ITEM 1:", TFTBP_NONE, LBL_TYPE_TITLE));
    telaTempoCiclos->addLabel(TFTLabel(&tft, 60, 70, "ITEM 2:", TFTBP_NONE, LBL_TYPE_TITLE));
    telaTempoCiclos->addLabel(TFTLabel(&tft, 60, 105, "ITEM 3:", TFTBP_NONE, LBL_TYPE_TITLE));
    telaTempoCiclos->addButton(TFTButton(&tft, 0, 0, "A", TFTBP_LEFT, BTN_TYPE_ARROW_LEFT,[](){Serial.println("Voltar");}));
    // menu inferior com botões
    //...
    // lblTitle.draw();
    // lblItem1.draw();
    // lblItem2.draw();
    // lblItem3.draw();
    // lblItem4.draw();
    // lblItem5.draw();
    // lblItem6.draw();
    // btnVoltar.draw();
    // btnUp.draw();
    // btnDown.draw();
    // btnMinus10.draw();
    // btnMinus1.draw();
    // btnPlus1.draw();
    // btnPlus10.draw();
    telaTempoCiclos->drawScreen();
}

unsigned long checkTime = millis();

void loop() {
    // check if TFT buttons is pressed using millis
    if (millis() > checkTime + 250) {
        telaTempoCiclos->readScreenButtons();
        // btnVoltar.onPress([]() {
        //     Serial.println("VOLTAR");
        // });
        // btnUp.onPress([]() {
        //     Serial.println("UP");
        // });
        // btnDown.onPress([]() {
        //     Serial.println("DOWN");
        // });
        // btnMinus10.onPress([]() {
        //     Serial.println("MINUS10");
        // });
        // btnMinus1.onPress([]() {
        //     Serial.println("MINUS1");
        // });
        // btnPlus1.onPress([]() {
        //     Serial.println("PLUS1");
        // });
        // btnPlus10.onPress([]() {
        //     Serial.println("PLUS10");
        // });
        checkTime = millis();
    }
}