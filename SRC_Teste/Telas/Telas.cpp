/*
updated: at least: 2022-08-24
*/

#include <Telas/Telas.h>

TFTScreen tft = TFTScreen();
Screen *tela = new Screen(&tft);

// Variable Labels
char botao0Tela2[20];

// seleciona a tela a ser exibida e à qual será feita a leitura dos botões
void initTela(TFTScreen *tft, Screen *tela, SCREEN_INDEX index) {
    clearScreen();

    switch (index) {
        case TELA_TITULO:
            TelaTitulo(tft, tela);
            break;
        case TELA_1:
            Tela1(tft, tela);
            break;
        case TELA_2:
            Tela2(tft, tela);
            break;
        case TELA_3:
            Tela3(tft, tela);
            break;
        case TELA_4:
            Tela4(tft, tela);
            break;
        default:
            break;
    }
    tela->draw();
}

int readButtonsTela(Screen *tela) {
    return tela->readButtons();
}

// RETORNO PARA TELA ANTERIOR
auto changeScreen = [](SCREEN_INDEX index) {
    if (tela != nullptr) {
        delete tela;
        delay(100);
    }
    tela = new Screen();
    initTela(&tft, tela, index);
};

// LIMPA OBJETOS
void clearVariableLabels() {
    botao0Tela2[0] = '    ';
}
void clearScreen() {
    clearVariableLabels();
    for (int i = 0; i < MAX_LABELS; i++) {
        tela->addLabel(i, TFTLabel(&tft, SCREEN_W + 50, SCREEN_H + 50, "", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    }
    for (int i = 0; i < MAX_BUTTONS; i++) {
        tela->addButton(i, TFTButton(&tft, SCREEN_W + 50, SCREEN_H + 50, "", OBJ_POS_NONE, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_TEXT, []() {}));
    }
    (&tft)->getTFT().fillScreen(BLACK);
}

// FUNÇÕES DE EXECUÇÃO
void execucaoTela1() {
    Serial.println("Executando Tela 1");
}

void execucaoTela2() {
    // assures tha button will be pressed only once
    static bool buttonPressed = false;
    if (!buttonPressed) {
        buttonPressed = true;
        int i = 5;
        unsigned long updateTemp = millis();

        do {
            if (millis() > updateTemp + 500) {
                itoa(i, botao0Tela2, 10);
               tela->changeLabel(1, botao0Tela2);
               
                updateTemp = millis();
                i++;
            }
            const int button = readButtonsTela(tela);
            if (button == 0 || button == 1) {  // botões troca de tela
                buttonPressed = false;
                return;
            }
        } while (i <= 10);
        Serial.println("Executando Tela 2");
        buttonPressed = false;
    }
}
void execucaoTela3() {
    Serial.println("Executando Tela 3");
}
void execucaoTela4() {
    Serial.println("Executando Tela 4");
}

// CRIAÇÃO DAS TELAS
void TelaTitulo(TFTScreen *tft, Screen *tela) {
    Serial.println("Tela de Título");
    tela->addLabel(0, TFTLabel(tft, 0, SCREEN_H / 4, "TELA DE", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 50, SCREEN_H / 2, "TITULO", OBJ_POS_CENTER, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    //"PHANTOM BUTTON*" (maYBE WILL BE USED ONLY BEFORE Arduino Mega solution)
    tela->addButton(2, TFTButton(tft, SCREEN_W, SCREEN_H, " ", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_TEXT, []() {}));
}
void Tela1(TFTScreen *tft, Screen *tela) {
    Serial.println("Tela 1");
    tela->addLabel(1, TFTLabel(tft, 0, 0, "TELA 1", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(2, TFTLabel(tft, 0, SCREEN_H / 3, "CLIQUE ABAIXO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    tela->addButton(0, TFTButton(tft, 50, 0, " ", OBJ_POS_RIGHT, BTN_TYPE_ARROW_RIGHT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_2); }));
    tela->addButton(1, TFTButton(tft, SCREEN_W, SCREEN_H / 2, "BOTAO", OBJ_POS_CENTER, BTN_TYPE_TEXT_RED, OBJ_SIZE_FIXED, []() { execucaoTela1(); }));
}
void Tela2(TFTScreen *tft, Screen *tela) {
    Serial.println("Tela 2");
    tela->addLabel(0, TFTLabel(tft, 0, 0, "TELA 2", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 0, 35, botao0Tela2, OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    tela->addButton(0, TFTButton(tft, 50, 0, " ", OBJ_POS_LEFT, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_1); }));
    tela->addButton(1, TFTButton(tft, 50, 0, " ", OBJ_POS_RIGHT, BTN_TYPE_ARROW_RIGHT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_3); }));
    tela->addButton(2, TFTButton(tft, SCREEN_W, SCREEN_H / 2, "BOTAO", OBJ_POS_CENTER, BTN_TYPE_TEXT_GREEN, OBJ_SIZE_FIXED, []() { execucaoTela2(); }));
}

unsigned long timerScreenCount = millis();
bool stopScreen = false;
void Tela3(TFTScreen *tft, Screen *tela) {
    timerScreenCount = millis();

    Serial.println("Tela 3");
    tela->addLabel(0, TFTLabel(tft, 0, 0, "TELA 3", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 0, SCREEN_H / 3, "CLIQUE ABAIXO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    tela->addButton(0, TFTButton(tft, 0, 0, " ", OBJ_POS_LEFT, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() {
                        changeScreen(TELA_2);
                    }));

    tela->addButton(1, TFTButton(tft, SCREEN_W, SCREEN_H / 2, "BOTAO", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() {
                        execucaoTela3();
                    }));
    tela->draw();

    while (1) {
        if (readButtonsTela(tela) == 0) {
            stopScreen = true;
        }
        if (stopScreen) {
            stopScreen = false;
            break;
        }

        if (millis() > timerScreenCount + 3000) {
            Tela4(tft, tela);
            break;
        }
    }
}




bool stopScreen4 = false;
static bool screen4on = false;
void Tela4(TFTScreen *tft, Screen *tela) {
    screen4on = true;
    Serial.println("Tela 4");
    tela->addLabel(0, TFTLabel(tft, 0, 0, "TELA 4", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 0, SCREEN_H / 3 - 15, "CLIQUE ABAIXO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    tela->addButton(0, TFTButton(tft, 0, 0, " ", OBJ_POS_LEFT, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_3); }));
    tela->addButton(1, TFTButton(tft, SCREEN_W, SCREEN_H / 2, "BOTAO", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { execucaoTela4(); }));
    tela->draw();
    if (screen4on) {
        unsigned long updateLabel = millis();
        char text[10];
        int num = 15;
        while (1) {
            if (millis() > updateLabel + 1000) {
                itoa(--num, text, 10);
                tela->changeLabel(1, text);
                updateLabel = millis();
            }

            if (readButtonsTela(tela) == 0) {
                stopScreen4 = true;
            }
            if (stopScreen4) {
                stopScreen4 = false;
                break;
            }
        }
    }
}