/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-08-21
    @version: 1.0
    @description
        Generate objects for TFT Button

*/

#pragma once

#include <TFTConfig.h>
#include <TFTScreen.h>

enum TFTObjectPosition {
    TFTBP_NONE,
    TFTBP_LEFT,
    TFTBP_RIGHT,
    TFTBP_CENTER
};

class TFTObject : public TFTScreen {
   protected:
    TFTScreen *tftScreen;
    unsigned short int x, y, w, h;
    unsigned short int padding;
    const char *title;
    TFTObjectPosition position;

   public:
    TFTObject();
    TFTObject(TFTScreen *tftScreen, int x, int y, const char *title, TFTObjectPosition position);

    TFTObject operator=(TFTObject tftObject);

    void draw();

    TFTScreen *getTFTScreen();

    int getX();
    int getY();
    int getW();
    int getH();
    int getPadding();   
    const char *getTitle();

    ~TFTObject();
};