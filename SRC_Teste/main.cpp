#include <main.h>

#include <TimerOne.h>

unsigned long checkTime = millis();

static int temperatura = 0;
void setTemperature() {
    temperatura++;
    if (temperatura > 100) {
        temperatura = 0;
    }
}
void getTemperature() {
    setTemperature();
    Serial.println("getTemperature: " + (String)temperatura);
}

void setup() {
    Serial.begin(9600);
    tft.setup(DRIVER, ROTATION);

    Timer1.initialize(500000);
    Timer1.attachInterrupt(getTemperature);

    //  initTela(&tft, tela, TELA_TITULO);
    //   delay(1500);
     initTela(&tft, tela, TELA_2);
}
void loop() {
    if (millis() > checkTime + 250) {
        readButtonsTela(tela);
        checkTime = millis();
    }
}
