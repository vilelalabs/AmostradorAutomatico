/*
    @author: Henrique Vilela
    @created: 2022-08-20
    @updated: 2022-09-23
    @version: 1.0
    @description
        - Declares TFTLabel class
        - Generate Label for TFTScreen  using TFTObject Class

*/

#pragma once

#include <TFTConfig.h>
#include <TFTObject.h>

enum LABEL_TYPE : uint8_t {
    LBL_TYPE_TITLE,  // Common text
    LBL_TYPE_DATA,   // Data text
};

class TFTLabel : public TFTObject {

   private:
    bool isNull = true;
    LABEL_TYPE type;

   public:
    TFTLabel();
    TFTLabel(TFTScreen *tftScreen, int x, int y, const char *title, TFTObjectPosition position, LABEL_TYPE type, TFTObjectSize objSize) : TFTObject(tftScreen, x, y, title, position, objSize) {
        this->isNull = false;
        this->type = type;
    }
    bool getIsNull();

    void draw();

    ~TFTLabel();
};