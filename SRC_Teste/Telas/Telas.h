#pragma once

#include <Screen.h>
#include <TimerOne.h>


extern TFTScreen tft;
extern Screen *tela;


enum SCREEN_INDEX {
    TELA_TITULO,
    TELA_1,
    TELA_2,
    TELA_3,
    TELA_4
};

void initTela(TFTScreen *tft, Screen *tela, SCREEN_INDEX index);
int readButtonsTela(Screen *tela);
void clearScreen();

// CRIAÇÃO DAS TELAS
void TelaTitulo(TFTScreen *tft, Screen *tela);
void Tela1(TFTScreen *tft, Screen *tela);
void Tela2(TFTScreen *tft, Screen *tela);
void Tela3(TFTScreen *tft, Screen *tela);
void Tela4(TFTScreen *tft, Screen *tela);