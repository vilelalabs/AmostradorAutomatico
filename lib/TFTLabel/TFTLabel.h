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

class TFTLabel : public TFTObject {
    using TFTObject::TFTObject;

   public:
    ~TFTLabel();
};