/*
    @author: Henrique Vilela
    @created: 2022-09-03
    @updated: 2022-09-03
    @version: 1.0
    @description
        Declares functions to activate heater
*/

#pragma once

#include <Arduino.h>

#define RES_LIGADA 0
#define RES_DESLIGADA 1

#define RESISTOR_PIN 51

void setupHeater();
void activateHeater(float temperature, float threshold);
void turnOffHeater();