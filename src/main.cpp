#include <main.h>

unsigned long checkTime = millis();
TFTScreen tft = TFTScreen();
Screen *tela;

void setup() {
    Serial.begin(9600);
    tft.setup(DRIVER, ROTATION);

    // changeScreen(TELA_TITULO);
    // delay(5000);
    // changeScreen(TELA_SELECAO_INICIAL);
    //  delay(5000);
    // changeScreen(TELA_CONFIGURACAO);
    //  delay(5000);
    // changeScreen(TELA_AGUARDANDO_TEMPERATURA);
    // delay(5000);
    // changeScreen(TELA_CONFIG_TEMPERATURA);
    // delay(5000);
    // changeScreen(TELA_CONFIG_CICLOS);
    // delay(5000);
    // changeScreen(TELA_INICIAR);
    // delay(5000);
    // changeScreen(TELA_SELECIONAR_CICLO);
    // delay(5000);
     changeScreen(TELA_EM_CICLO);
    // delay(5000);

}

void loop() {
    if (millis() > checkTime + 250) {
        readButtonsTela(tela);
        checkTime = millis();
    }
}

void changeScreen(SCREEN_INDEX index) {
    if (tela != nullptr) {
        delete tela;
        delay(100);
    }

    tela = new Screen();
    initTela(&tft, tela, index);
}