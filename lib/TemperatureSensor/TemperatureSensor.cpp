
#include <TemperatureSensor.h>
#include <DHT.h>

DHT dht(TEMPERATURE_SENSOR_PIN, DHT11);

void setupTemperatureSensor() {
    dht.begin();
}

//=============================================================================

float getTemperature() {
    //int tempValue = analogRead(TEMPERATURE_SENSOR_PIN);
    float tempValue = dht.readTemperature();
    return tempValue;
}