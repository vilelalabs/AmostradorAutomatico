/*
    @author: Henrique Vilela
    @created: 2022-08-30
    @updated: 2022-09-23
    @version: 1.0
    @description
        Implements functions for Temperature Sensor Actions
*/

#include <TemperatureSensor.h>

// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(ONE_WIRE_BUS);

// instancias para os sensores
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

//--------------------------------------------------------------------------
void setupTemperatureSensor() {
    sensors.begin();
    if (!sensors.getAddress(sensor1, 0)) {
        Serial.println("Sensor de temperatura nao encontrado!");
    }
}

//--------------------------------------------------------------------------
float getTemperature() {
    sensors.requestTemperatures();
    float tempValue = sensors.getTempC(sensor1);

    return tempValue;
}