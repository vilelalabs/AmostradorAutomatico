#pragma once

#include <Arduino.h>
#include <DHT.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#define SENSOR_PIN A8

#define ONE_WIRE_BUS SENSOR_PIN

void setupTemperatureSensor();
float getTemperature();
