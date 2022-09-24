/*
    @author: Henrique Vilela
    @created: 2022-08-30
    @updated: 2022-09-02
    @version: 1.0
    @description
        Declares functions for Temperature Sensor Actions
*/

#pragma once

#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#define SENSOR_PIN A8

#define ONE_WIRE_BUS SENSOR_PIN

void setupTemperatureSensor();
float getTemperature();
