
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

    // initTela(&tft, tela, TELA_TITULO);
    // delay(4000);
    // initTela(&tft, tela, TELA_SELECAO_INICIAL);
    //   delay(5000);
    // initTela(&tft, tela, TELA_CONFIGURACAO);
    //  delay(5000);
    // initTela(&tft, tela, TELA_AGUARDANDO_TEMPERATURA);
    // delay(5000);
    // initTela(&tft, tela, TELA_CONFIG_TEMPERATURA);
    // delay(5000);
    // initTela(&tft, tela, TELA_CONFIG_CICLOS);
    // delay(5000);
    // initTela(&tft, tela, TELA_INICIAR);
    // delay(5000);
     initTela(&tft, tela, TELA_SELECIONAR_CICLO);
    // delay(5000);
    // initTela(&tft, tela, TELA_EM_CICLO);
    // delay(5000);

    // initTela(&tft, tela, TELA_TESTE);
}

void loop() {
    if (millis() > checkTime + 250) {
        readButtonsTela(tela);
        checkTime = millis();
    }
}
