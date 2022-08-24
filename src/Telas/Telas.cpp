
#include <Telas/Telas.h>

void initTela(TFTScreen *tft, Screen *tela, SCREEN_INDEX index) {
    switch (index) {
        case TELA_TITULO:
            TelaTitulo(tft, tela);
            break;
        case TELA_SELECAO_INICIAL:
            TelaSelecaoInicial(tft, tela);
            break;
        case TELA_CONFIGURACAO:
            TelaConfiguracao(tft, tela);
            break;
        case TELA_AGUARDANDO_TEMPERATURA:
            TelaAguardandoTemperatura(tft, tela);
            break;
        case TELA_CONFIG_TEMPERATURA:
            TelaConfigTemperatura(tft, tela);
            break;
        case TELA_CONFIG_CICLOS:
            TelaConfigCiclos(tft, tela);
            break;
        case TELA_INICIAR:
            TelaIniciar(tft, tela);
            break;
        case TELA_SELECIONAR_CICLO:
            TelaSelecionarCiclo(tft, tela);
            break;
        case TELA_EM_CICLO:
            TelaEmCiclo(tft, tela);
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

// CRIAÇÃO DAS TELAS
void TelaTitulo(TFTScreen *tft, Screen *tela) {
    tela->addLabel(0, TFTLabel(tft, 0, SCREEN_H / 4, "AMOSTRADOR", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 50, SCREEN_H / 2, "AUTOMATICO", OBJ_POS_CENTER, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    //"PHANTOM BUTTON*" (USED BEFORE Arduino mega solution)
    tela->addButton(4, TFTButton(tft, SCREEN_W, SCREEN_H, " ", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_TEXT, []() {}));
}

void TelaSelecaoInicial(TFTScreen *tft, Screen *tela) {
    // Example LABEL tela->addLabel(0, TFTLabel(tft, SCREEN_W / 2, 125, "22x", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    // Example Button tela->addButton(0, TFTButton(tft, 0, 45, "A", OBJ_POS_RIGHT, BTN_TYPE_ARROW_UP, OBJ_SIZE_TEXT, []() { Serial.println("UP"); }));

    tela->addLabel(0, TFTLabel(tft, 0, 0, "AMOSTRADOR AUTOMATICO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addButton(0, TFTButton(tft, 0, SCREEN_H / 2 - 50, "CONFIGURACAO", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { Serial.println("CONFIGURACAO"); }));
    tela->addButton(1, TFTButton(tft, 0, SCREEN_H / 2 + 30, "INICIAR", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { Serial.println("INICIAR"); }));
}
void TelaConfiguracao(TFTScreen *tft, Screen *tela) {
}
void TelaAguardandoTemperatura(TFTScreen *tft, Screen *tela) {
}
void TelaConfigTemperatura(TFTScreen *tft, Screen *tela) {
}
void TelaConfigCiclos(TFTScreen *tft, Screen *tela) {
    // Title
    tela->addLabel(0, TFTLabel(tft, 0, 0, "Menu - Tal", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    //
    tela->addLabel(1, TFTLabel(tft, 60, 55, "ITEM 1:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(2, TFTLabel(tft, 60, 90, "ITEM 2:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(3, TFTLabel(tft, 60, 125, "ITEM 3:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(4, TFTLabel(tft, SCREEN_W / 2, 55, "00x", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(5, TFTLabel(tft, SCREEN_W / 2, 90, "11x", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(6, TFTLabel(tft, SCREEN_W / 2, 125, "22x", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    // Options

    tela->addButton(0, TFTButton(tft, 0, 45, "A", OBJ_POS_RIGHT, BTN_TYPE_ARROW_UP, OBJ_SIZE_TEXT, []() { Serial.println("UP"); }));
    tela->addButton(1, TFTButton(tft, 0, 105, "A", OBJ_POS_RIGHT, BTN_TYPE_ARROW_DOWN, OBJ_SIZE_TEXT, []() { Serial.println("DOWN"); }));

    // // Navigation
    tela->addButton(2, TFTButton(tft, 0, SCREEN_H - 50, "AAA", OBJ_POS_LEFT, BTN_TYPE_TENTH_MINUS10, OBJ_SIZE_TEXT, []() { Serial.println("MINUS10"); }));
    tela->addButton(3, TFTButton(tft, 100, SCREEN_H - 50, "ZZ", OBJ_POS_NONE, BTN_TYPE_TEXT_GREEN, OBJ_SIZE_TEXT, []() { Serial.println("ZZ"); }));
    // tela->addButton(4, TFTButton(tft, SCREEN_W - 150, SCREEN_H - 50, "ZZ", OBJ_POS_NONE, BTN_TYPE_TEXT_RED,OBJ_SIZE_TEXT, []() {}));
    // tela->addButton(5, TFTButton(tft, 220, SCREEN_H - 50, "AAA", OBJ_POS_RIGHT, BTN_TYPE_TENTH_PLUS10,OBJ_SIZE_TEXT, []() {}));

    // Voltar para a tela inicial
    // tela->addButton(6, TFTButton(tft, 0, 0, "TEXT", OBJ_POS_LEFT, BTN_TYPE_TEXT_GREEN, []() {}));
}
void TelaIniciar(TFTScreen *tft, Screen *tela) {
}
void TelaSelecionarCiclo(TFTScreen *tft, Screen *tela) {
}
void TelaEmCiclo(TFTScreen *tft, Screen *tela) {
}
