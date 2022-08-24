#include <Arduino.h>
#include <TFTButton.h>
#include <TFTConfig.h>
#include <TFTLabel.h>
#include <TFTScreen.h>
#include <Screen.h>

#include <Telas/Telas.h>

unsigned long checkTime = millis();
TFTScreen tft = TFTScreen();
Screen *telaAbertura;
Screen *telaMenu;

void setup() {
    Serial.begin(9600);
    tft.setup(DRIVER, ROTATION);

    telaAbertura = new Screen();
    initTelaAbertura(&tft, telaAbertura);
    delay(5000);
    delete telaAbertura;
    delay(5000);
    telaMenu = new Screen();
    initTelaAbertura(&tft, telaMenu);
}

void loop() {
    if (millis() > checkTime + 100) {
        readButtonsTelaAbertura(telaAbertura);
        checkTime = millis();
    }
}