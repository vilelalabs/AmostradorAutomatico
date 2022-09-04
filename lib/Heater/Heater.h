#pragma once

#include <Arduino.h>

#define RES_LIGADA 1
#define RES_DESLIGADA 0

#define RESISTOR_PIN 50

void setupHeater();

void activateHeater(float temperature, float threshold);

void turnOffHeater();