#pragma once

#include <Arduino.h>
//#include <TimerOne.h>

#define TEMPERATURE_SENSOR_PIN A8

void setupTemperatureSensor();

float getTemperature();
