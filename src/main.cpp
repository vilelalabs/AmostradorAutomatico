/*
    @author: Henrique Vilela
    @created: 2022-08-22
    @updated: 2022-09-23
    @version: 1.0
    @description
        - Main file for the project
        - Initializes all the components, timers, EEPROM memory and starts the main loop

*/

#include <main.h>

unsigned long checkTime = millis();

void setup() {
    Serial.begin(9600);
    Serial.println("Starting...");
    tft.setup(DRIVER, ROTATION);

    // garante que dados estão zerados na primeira vez que o programa é executado neste dispositivo
    checkFirstRun();
    // Garante início sempre do ciclo 1
    EEPROMWriteInt(CICLO_INICIAL_EEPROM_ADDRESS, 1);

    // inicializa o sensor de temperatura
    setupTemperatureSensor();

    // inicializa válvulas
    setupValvulas();

    // inicializa o aquecedor
    setupHeater();

    initTela(&tft, tela, TELA_TITULO);
    delay(4000);
    initTela(&tft, tela, TELA_SELECAO_INICIAL);
}

void loop() {
    if (millis() > checkTime + 250) {
        readButtonsTela(tela);
        checkTime = millis();
    }
}
