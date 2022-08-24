
#include <Screen.h>

#pragma once

enum SCREEN_INDEX {
    TELA_ABERTURA,
    TELA_CICLO,
    //....
};

void initTela(TFTScreen *tft, Screen *tela, SCREEN_INDEX index);

void readButtonsTela(Screen *tela);

// CRIAÇÃO DAS TELAS
void TelaAbertura(TFTScreen *tft, Screen *tela);
void TelaCiclo(TFTScreen *tft, Screen *tela);