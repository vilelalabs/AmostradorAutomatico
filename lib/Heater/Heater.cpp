#include <Heater.h>

static bool resistorStatus = RES_DESLIGADA;

void setupHeater() {
    pinMode(RESISTOR_PIN, OUTPUT);
    digitalWrite(RESISTOR_PIN, RES_DESLIGADA);
}

void activateHeater(float temperature, float threshold) {
    if (temperature <= threshold - 1 && resistorStatus != RES_LIGADA) {
        Serial.println("Ligando Aquecedor.");
        digitalWrite(RESISTOR_PIN, RES_LIGADA);
        resistorStatus = RES_LIGADA;
    } else if (temperature > threshold && resistorStatus == RES_LIGADA) {
        Serial.println("Desligando Aquecedor.");
        digitalWrite(RESISTOR_PIN, RES_DESLIGADA);
        resistorStatus = RES_DESLIGADA;
    }
}

void turnOffHeater() {
    Serial.println("Desligamento forçado do Aquecedor!");
    digitalWrite(RESISTOR_PIN, RES_DESLIGADA);
    resistorStatus = RES_DESLIGADA;
}
