#include <Arduino.h>
#include <TFTButton.h>
#include <TFTConfig.h>
#include <TFTLabel.h>
#include <TFTScreen.h>
#include <Screen.h>

#include <Telas/Telas.h>

unsigned long checkTime = millis();
TFTScreen tft = TFTScreen();
Screen *tela;

void setup() {
    Serial.begin(9600);
    tft.setup(DRIVER, ROTATION);

    tela = new Screen();
    initTela(&tft, tela, TELA_ABERTURA);
    delay(5000);
    delete tela;
    delay(200);
    tela = new Screen();
    initTela(&tft, tela, TELA_CICLO);
}

void loop() {
    if (millis() > checkTime + 100) {
        readButtonsTela(tela);
        checkTime = millis();
    }
}