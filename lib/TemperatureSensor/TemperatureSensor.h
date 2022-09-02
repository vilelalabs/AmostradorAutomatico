#pragma once

#include <Arduino.h>

#define TEMPERATURE_SENSOR_PIN A8

void setupTemperatureSensor();

float getTemperature();
