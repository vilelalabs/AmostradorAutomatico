/*
    @author: Henrique Vilela
    @created: 2022-08-23
    @updated: 2022-08-23
    @version: 1.0
    @description
        Generate All Screens for TFT Project
*/

#pragma once

#include <TFTButton.h>
#include <TFTConfig.h>
#include <TFTLabel.h>

// INICIALIZAÇÕES DA TELA TFT
//TFTScreen telaTempoCiclos = TFTScreen();

// // Voltar para a tela inicial
// TFTButton btnVoltar = TFTButton(&telaTempoCiclos, 0, 0, "A", TFTBP_LEFT, BTN_TYPE_ARROW_LEFT);

// // Title
// TFTLabel lblTitle = TFTLabel(&telaTempoCiclos, 0, 0, "Menu - Tal", TFTBP_CENTER, LBL_TYPE_TITLE);

// TFTLabel lblItem1 = TFTLabel(&telaTempoCiclos, 60, 55, "ITEM 1:", TFTBP_NONE, LBL_TYPE_TITLE);
// TFTLabel lblItem2 = TFTLabel(&telaTempoCiclos, 60, 90, "ITEM 2:", TFTBP_NONE, LBL_TYPE_TITLE);
// TFTLabel lblItem3 = TFTLabel(&telaTempoCiclos, 60, 125, "ITEM 3:", TFTBP_NONE, LBL_TYPE_TITLE);
// TFTLabel lblItem4 = TFTLabel(&telaTempoCiclos, lblItem1.getX() + lblItem1.getW(), 55, "00x", TFTBP_NONE, LBL_TYPE_DATA);
// TFTLabel lblItem5 = TFTLabel(&telaTempoCiclos, lblItem2.getX() + lblItem2.getW(), 90, "11x", TFTBP_NONE, LBL_TYPE_DATA);
// TFTLabel lblItem6 = TFTLabel(&telaTempoCiclos, lblItem3.getX() + lblItem3.getW(), 125, "22x", TFTBP_NONE, LBL_TYPE_DATA);

// // Options

// TFTButton btnUp = TFTButton(&telaTempoCiclos, 0, 45, "A", TFTBP_RIGHT, BTN_TYPE_ARROW_UP);
// TFTButton btnDown = TFTButton(&telaTempoCiclos, 0, 105, "A", TFTBP_RIGHT, BTN_TYPE_ARROW_DOWN);

// // Navigation
// TFTButton btnMinus10 = TFTButton(&telaTempoCiclos, 0, SCREEN_H - 50, "AAA", TFTBP_LEFT, BTN_TYPE_TENTH_MINUS10);
// TFTButton btnMinus1 = TFTButton(&telaTempoCiclos, 100, SCREEN_H - 50, "A", TFTBP_NONE, BTN_TYPE_ARROW_LEFT);
// TFTButton btnPlus1 = TFTButton(&telaTempoCiclos, SCREEN_W - 150, SCREEN_H - 50, "A", TFTBP_NONE, BTN_TYPE_ARROW_RIGHT);
// TFTButton btnPlus10 = TFTButton(&telaTempoCiclos, 220, SCREEN_H - 50, "AAA", TFTBP_RIGHT, BTN_TYPE_TENTH_PLUS10);

// Draw all screens
class Screen {
    private:
     TFTLabel *labels;
     TFTButton *buttons;
     unsigned short labelCount = 0;
     unsigned short buttonCount = 0;

    public:
     Screen();

     void addLabel(TFTLabel label);
     void addButton(TFTButton button);
     void drawScreen();
     void readScreenButtons();

     ~Screen();
};