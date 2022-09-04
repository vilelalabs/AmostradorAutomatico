
#include <TemperatureSensor.h>

//DHT Apenas para testes de bancada
//DHT dht(SENSOR_PIN, DHT11);

// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(ONE_WIRE_BUS);

// instanciações  para os sensores
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

void setupTemperatureSensor() {
    //dht.begin();
    sensors.begin();
    if (!sensors.getAddress(sensor1, 0)) {
        Serial.println("Sensor de temperatura nao encontrado!");
    }
}

//=============================================================================

float getTemperature() {
    //float tempValue = dht.readTemperature();

    sensors.requestTemperatures();
    // COM O SENSOR FINAL
    float tempValue = sensors.getTempC(sensor1);

    return tempValue;
}