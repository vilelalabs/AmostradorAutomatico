#include <main.h>

unsigned long checkTime = millis();
TFTScreen tft = TFTScreen();
Screen *tela;

void setup() {
    Serial.begin(9600);
    tft.setup(DRIVER, ROTATION);

    changeScreen(TELA_ABERTURA);
    delay(1000);
    changeScreen(TELA_CICLO);
    delay(1000);
    // changeScreen(TELA3);
}

void loop() {
    if (millis() > checkTime + 250) {
        readButtonsTela(tela);
        checkTime = millis();
    }
}

void changeScreen(SCREEN_INDEX index) {
    if(tela != nullptr) {
        delete tela;
        delay(100);
    }

    tela = new Screen();
    initTela(&tft, tela, index);
}