/*
updated: at least: 2022-08-24
*/

#include <Telas/Telas.h>

TFTScreen tft = TFTScreen();
Screen *tela = new Screen();

void initTela(TFTScreen *tft, Screen *tela, SCREEN_INDEX index) {
    switch (index) {
        case TELA_TITULO:
            TelaTitulo(tft, tela);
            break;
        case TELA_1:
            Tela1(tft, tela);
            break;
        case TELA_2:
            Tela2(tft, tela);
            break;
        case TELA_3:
            Tela3(tft, tela);
            break;

        default:
            break;
    }
    tft->getTFT().fillScreen(BLACK);
    tela->draw();
}

void readButtonsTela(Screen *tela) {
    tela->readButtons();
}

// RETORNO PARA TELA ANTERIOR
auto changeScreen = [](SCREEN_INDEX index) {
    if (tela != nullptr) {
        delete tela;
        delay(100);
    }
    tela = new Screen();
    initTela(&tft, tela, index);
};

// FUNÇÕES DE EXECUÇÃO
void execucaoTela1() {
    Serial.println("Executando Tela 1");
}
void execucaoTela2() {
    Serial.println("Executando Tela 2");
}
void execucaoTela3() {
    Serial.println("Executando Tela 3");
}

// CRIAÇÃO DAS TELAS
void TelaTitulo(TFTScreen *tft, Screen *tela) {
    tela->addLabel(0, TFTLabel(tft, 0, SCREEN_H / 4, "TELA DE", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 50, SCREEN_H / 2, "TITULO", OBJ_POS_CENTER, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    //"PHANTOM BUTTON*" (maYBE WILL BE USED ONLY BEFORE Arduino Mega solution)
    tela->addButton(2, TFTButton(tft, SCREEN_W, SCREEN_H, " ", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_TEXT, []() {}));
}
void Tela1(TFTScreen *tft, Screen *tela) {
    tela->addLabel(0, TFTLabel(tft, 0, 0, "TELA 1", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 0, SCREEN_H / 3, "CLIQUE ABAIXO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    tela->addButton(0, TFTButton(tft, 50, 0, " ", OBJ_POS_RIGHT, BTN_TYPE_ARROW_RIGHT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_2); }));
    tela->addButton(1, TFTButton(tft, SCREEN_W, SCREEN_H / 2, "BOTAO", OBJ_POS_CENTER, BTN_TYPE_TEXT_RED, OBJ_SIZE_FIXED, []() { execucaoTela1(); }));
}
void Tela2(TFTScreen *tft, Screen *tela) {
    tela->addLabel(0, TFTLabel(tft, 0, 0, "TELA 2", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 0, SCREEN_H / 3, "CLIQUE ABAIXO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    tela->addButton(0, TFTButton(tft, 50, 0, " ", OBJ_POS_LEFT, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_1); }));
    tela->addButton(2, TFTButton(tft, 50, 0, " ", OBJ_POS_RIGHT, BTN_TYPE_ARROW_RIGHT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_3); }));
    tela->addButton(1, TFTButton(tft, SCREEN_W, SCREEN_H / 2, "BOTAO", OBJ_POS_CENTER, BTN_TYPE_TEXT_GREEN, OBJ_SIZE_FIXED, []() { execucaoTela2(); }));
}
void Tela3(TFTScreen *tft, Screen *tela) {
    tela->addLabel(0, TFTLabel(tft, 0, 0, "TELA 3", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 0, SCREEN_H / 3, "CLIQUE ABAIXO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    tela->addButton(0, TFTButton(tft, 0, 0, " ", OBJ_POS_LEFT, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_2); }));
    tela->addButton(1, TFTButton(tft, SCREEN_W, SCREEN_H / 2, "BOTAO", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { execucaoTela3(); }));
}