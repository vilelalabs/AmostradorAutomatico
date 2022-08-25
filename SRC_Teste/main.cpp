#include <main.h>


unsigned long checkTime = millis();

void setup() {
    Serial.begin(9600);
    tft.setup(DRIVER, ROTATION);

     initTela(&tft, tela, TELA_TITULO);
     delay(1500);
     initTela(&tft, tela, TELA_1);
}
void loop() {
    if (millis() > checkTime + 250) {
        readButtonsTela(tela);
        checkTime = millis();
    }
}
