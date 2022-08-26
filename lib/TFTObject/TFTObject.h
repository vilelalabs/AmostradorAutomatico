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

#define FIXED_WIDTH (180) //default first: 180
#define FIXED_HEIGHT (60)

enum TFTObjectPosition : uint8_t {
    OBJ_POS_NONE,
    OBJ_POS_LEFT,
    OBJ_POS_RIGHT,
    OBJ_POS_CENTER
};
enum TFTObjectSize : uint8_t {
    OBJ_SIZE_FIXED,
    OBJ_SIZE_TEXT
};

class TFTObject : public TFTScreen {
   protected:
    TFTScreen *tftScreen;
    unsigned short x, y, w, h;

    uint8_t padding;
    const char *title;
    uint8_t textWidth;
    uint8_t textHeight;

    TFTObjectPosition position;
    TFTObjectSize objSize;

   public:
    TFTObject();
    TFTObject(TFTScreen *tftScreen, int x, int y, const char *title, TFTObjectPosition position, TFTObjectSize ojbSize);

    TFTObject operator=(TFTObject tftObject);

    void draw(); // override

    TFTScreen *getTFTScreen();

    int getX();
    int getY();
    int getW();
    int getH();
    uint8_t getPadding();
    uint8_t getObjSize();
    const char *getTitle();
    uint8_t getTextWidth();
    uint8_t getTextHeight();

    ~TFTObject();
};