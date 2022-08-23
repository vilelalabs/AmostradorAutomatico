/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-08-21
    @version: 1.0
    @description
        Generate Label for TFTScreen

*/

#pragma once

#include <TFTConfig.h>
#include <TFTObject.h>

enum LABEL_TYPE {
    LBL_TYPE_TITLE,  // Common text
    LBL_TYPE_DATA,   // Data text
};

class TFTLabel : public TFTObject {
    // using TFTObject::TFTObject;

   private:
    LABEL_TYPE type;

   public:
    TFTLabel(TFTScreen *tftScreen, int x, int y, const char *title, TFTObjectPosition position, LABEL_TYPE type) : TFTObject(tftScreen, x, y, title, position) {
        this->type = type;
    }

    void draw();

    ~TFTLabel();
};