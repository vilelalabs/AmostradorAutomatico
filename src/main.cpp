#include <main.h>

unsigned long checkTime = millis();
TFTScreen tft = TFTScreen();
Screen *tela;

void setup() {
    Serial.begin(9600);
    tft.setup(DRIVER, ROTATION);

    Serial.println((int)sizeof(uint8_t));
    Serial.println((int)sizeof(uint16_t));
    Serial.println((int)sizeof(unsigned short));

    changeScreen(TELA_TITULO);
    delay(1000);
    changeScreen(TELA_SELECAO_INICIAL);
    delay(1000);
    //changeScreen(TELA_CONFIG_CICLOS);
    //delay(1000);
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