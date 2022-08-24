
#include <Telas/Telas.h>


void initTelaAbertura(TFTScreen *tft, Screen *tela) {


    // Title
    //telaAbertura->addLabel(0, TFTLabel(tft, 0, 0, "Menu - Tal", TFTBP_CENTER, LBL_TYPE_TITLE));

    //
    tela->addLabel(1, TFTLabel(tft, 60, 55, "ITEM 1:", TFTBP_NONE, LBL_TYPE_TITLE));
    tela->addLabel(2, TFTLabel(tft, 60, 90, "ITEM 2:", TFTBP_NONE, LBL_TYPE_TITLE));
    tela->addLabel(3, TFTLabel(tft, 60, 125, "ITEM 3:", TFTBP_NONE, LBL_TYPE_TITLE));
    tela->addLabel(4, TFTLabel(tft, SCREEN_W/2, 55, "00x", TFTBP_NONE, LBL_TYPE_DATA));
    tela->addLabel(5, TFTLabel(tft, SCREEN_W/2, 90, "11x", TFTBP_NONE, LBL_TYPE_DATA));
    tela->addLabel(6, TFTLabel(tft, SCREEN_W/2, 125, "22x", TFTBP_NONE, LBL_TYPE_DATA));
    tela->draw();

    // Options   

    tela->addButton(0, TFTButton(tft, 0, 45, "A", TFTBP_RIGHT, BTN_TYPE_ARROW_UP, []() {Serial.println("UP");}));
    tela->addButton(1, TFTButton(tft, 0, 105, "A", TFTBP_RIGHT, BTN_TYPE_ARROW_DOWN, []() {Serial.println("DOWN");}));

    // // Navigation
    tela->addButton(2, TFTButton(tft, 0, SCREEN_H - 50, "AAA", TFTBP_LEFT, BTN_TYPE_TENTH_MINUS10, []() {Serial.println("MINUS10");}));
    tela->addButton(3, TFTButton(tft, 100, SCREEN_H - 50, "ZZ", TFTBP_NONE, BTN_TYPE_TEXT_GREEN, []() { Serial.println("ZZ");}));
    //tela->addButton(4, TFTButton(tft, SCREEN_W - 150, SCREEN_H - 50, "ZZ", TFTBP_NONE, BTN_TYPE_TEXT_RED, []() {}));
    //tela->addButton(5, TFTButton(tft, 220, SCREEN_H - 50, "AAA", TFTBP_RIGHT, BTN_TYPE_TENTH_PLUS10, []() {}));

    // Voltar para a tela inicial
    //tela->addButton(6, TFTButton(tft, 0, 0, "TEXT", TFTBP_LEFT, BTN_TYPE_TEXT_GREEN, []() {}));

    tela->draw();
}

void readButtonsTelaAbertura(Screen *tela) {
    tela->readButtons();
}

