#pragma once
#include <Screen.h>

extern TFTScreen tft;
extern Screen *tela;

enum SCREEN_INDEX {
    TELA_TITULO,
    TELA_1,
    TELA_2,
    TELA_3
};


void initTela(TFTScreen *tft, Screen *tela, SCREEN_INDEX index);

void readButtonsTela(Screen *tela);

// CRIAÇÃO DAS TELAS
void TelaTitulo(TFTScreen *tft, Screen *tela);
void Tela1(TFTScreen *tft, Screen *tela);
void Tela2(TFTScreen *tft, Screen *tela);
void Tela3(TFTScreen *tft, Screen *tela);