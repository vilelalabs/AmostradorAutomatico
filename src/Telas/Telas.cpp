/*
updated: at least: 2022-08-24
*/

#include <Telas/Telas.h>

TFTScreen tft = TFTScreen();
Screen *tela = new Screen();

// seleciona a tela a ser exibida e à qual será feita a leitura dos botões
void initTela(TFTScreen *tft, Screen *tela, SCREEN_INDEX index) {
    clearScreen();

    switch (index) {
        case TELA_TITULO:
            TelaTitulo(tft, tela);
            break;
        case TELA_SELECAO_INICIAL:
            TelaSelecaoInicial(tft, tela);
            break;
        case TELA_CONFIGURACAO:
            TelaConfiguracao(tft, tela);
            break;
        case TELA_AGUARDANDO_TEMPERATURA:
            TelaAguardandoTemperatura(tft, tela);
            break;
        case TELA_CONFIG_TEMPERATURA:
            TelaConfigTemperatura(tft, tela);
            break;
        case TELA_CONFIG_CICLOS:
            TelaConfigCiclos(tft, tela);
            break;
        case TELA_INICIAR:
            TelaIniciar(tft, tela);
            break;
        case TELA_SELECIONAR_CICLO:
            TelaSelecionarCiclo(tft, tela);
            break;
        case TELA_EM_CICLO:
            TelaEmCiclo(tft, tela);
            break;
        case TELA_TESTE:
            TelaTeste(tft, tela);
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

// VARIÁVEIS GLOBAIS PARA INTERAÇÕES COM A TELA E PROCESSOS DE TIMER (EX: MILLIS)
//----Labels Varáveis (LV)----
//-- LV - TelaEmCiclo --
static bool executandoTelaEmCiclo = false;
char statusTelaEmCiclo[12]      = "           ";
char cicloTelaEmCiclo[5]        = "    ";
char temperaturaTelaEmCiclo[5]  = "    ";
char tempoTelaEmCiclo[5]        = "    ";

// FUNÇÕES DE EXECUÇÃO INDIVIDUAIS DOS BOTÕES

// LIMPA OBJETOS
void clearVariableLabels() {
    // insert all variable Labels here
    statusTelaEmCiclo[0] = ' ';
    cicloTelaEmCiclo[0] = ' ';
    temperaturaTelaEmCiclo[0] = ' ';
    tempoTelaEmCiclo[0] = ' ';
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

// CRIAÇÃO DAS TELAS
void TelaTitulo(TFTScreen *tft, Screen *tela) {
    tela->addLabel(0, TFTLabel(tft, 0, SCREEN_H / 4, "AMOSTRADOR", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 50, SCREEN_H / 2, "AUTOMATICO", OBJ_POS_CENTER, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    //"PHANTOM BUTTON*" (maYBE WILL BE USED ONLY BEFORE Arduino Mega solution)
    tela->addButton(0, TFTButton(tft, SCREEN_W, SCREEN_H, " ", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_TEXT, []() {}));
}
void TelaSelecaoInicial(TFTScreen *tft, Screen *tela) {
    tela->addLabel(0, TFTLabel(tft, 0, 0, "AMOSTRADOR AUTOMATICO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addButton(0, TFTButton(tft, 0, SCREEN_H / 2 - 50, "CONFIGURACAO", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { changeScreen(TELA_CONFIGURACAO); }));
    tela->addButton(1, TFTButton(tft, 0, SCREEN_H / 2 + 30, "INICIAR", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { changeScreen(TELA_AGUARDANDO_TEMPERATURA); }));
}
void TelaConfiguracao(TFTScreen *tft, Screen *tela) {
    tela->addLabel(0, TFTLabel(tft, 0, 0, "CONFIGURACAO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addButton(0, TFTButton(tft, 0, 0, "<", OBJ_POS_LEFT, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_SELECAO_INICIAL); }));
    tela->addButton(1, TFTButton(tft, 0, SCREEN_H / 2 - 50, "TEMPERATURA", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { changeScreen(TELA_CONFIG_TEMPERATURA); }));
    tela->addButton(2, TFTButton(tft, 0, SCREEN_H / 2 + 30, "T. CICLOS", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { changeScreen(TELA_CONFIG_CICLOS); }));
}
void TelaAguardandoTemperatura(TFTScreen *tft, Screen *tela) {
    // Title of Screen
    tela->addLabel(0, TFTLabel(tft, 0, 0, "AGUARDANDO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 0, 30, "TEMPERATURA", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    tela->addLabel(2, TFTLabel(tft, 90, 75, "ATUAL:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(3, TFTLabel(tft, 190, 75, "XXoC", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(4, TFTLabel(tft, 30, 115, "PROGRAMADA:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(5, TFTLabel(tft, 190, 115, "XXoC", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    // removed due ARDUINO UNO memory limitation, put back with MEGA
    tela->addButton(0, TFTButton(tft, 0, 170, "VOLTAR", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { changeScreen(TELA_SELECAO_INICIAL); }));
}
void TelaConfigTemperatura(TFTScreen *tft, Screen *tela) {
    // Title
    tela->addLabel(0, TFTLabel(tft, 0, 0, "TEMPERATURA", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    // Data
    tela->addLabel(1, TFTLabel(tft, 60, 75, "ATUAL:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(2, TFTLabel(tft, 60, 120, "DESEJADA:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(4, TFTLabel(tft, SCREEN_W / 2 + 20, 75, "75oC", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(5, TFTLabel(tft, SCREEN_W / 2 + 20, 120, "85oC", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    // Back to previous screen
    tela->addButton(0, TFTButton(tft, 0, 0, " ", OBJ_POS_LEFT, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_CONFIGURACAO); }));

    // Navigation
    tela->addButton(1, TFTButton(tft, 0, SCREEN_H - 50, "AAA", OBJ_POS_LEFT, BTN_TYPE_TENTH_MINUS10, OBJ_SIZE_TEXT, []() { Serial.println("-10"); }));
    tela->addButton(2, TFTButton(tft, 100, SCREEN_H - 50, "Z", OBJ_POS_NONE, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { Serial.println("-1"); }));
    tela->addButton(3, TFTButton(tft, SCREEN_W - 150, SCREEN_H - 50, "Z", OBJ_POS_NONE, BTN_TYPE_ARROW_RIGHT, OBJ_SIZE_TEXT, []() { Serial.println("+1"); }));
    tela->addButton(4, TFTButton(tft, 0, SCREEN_H - 50, "AAA", OBJ_POS_RIGHT, BTN_TYPE_TENTH_PLUS10, OBJ_SIZE_TEXT, []() { Serial.println("+10"); }));
}
void TelaConfigCiclos(TFTScreen *tft, Screen *tela) {
    // Title
    tela->addLabel(0, TFTLabel(tft, 0, 0, "TEMPO - CICLOS", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    // Data
    tela->addLabel(1, TFTLabel(tft, 60, 55, "LIMPEZA:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(2, TFTLabel(tft, 60, 90, "INSERCAO:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(3, TFTLabel(tft, 60, 125, "COLETA:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(4, TFTLabel(tft, SCREEN_W / 2 + 20, 55, "15s", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(5, TFTLabel(tft, SCREEN_W / 2 + 20, 90, "13s", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(6, TFTLabel(tft, SCREEN_W / 2 + 20, 125, "19s", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    // Back to previous screen
    tela->addButton(0, TFTButton(tft, 0, 0, " ", OBJ_POS_LEFT, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_CONFIGURACAO); }));

    // Options
    tela->addButton(1, TFTButton(tft, 0, 60, "A", OBJ_POS_RIGHT, BTN_TYPE_ARROW_UP, OBJ_SIZE_TEXT, []() { Serial.println("UP"); }));
    tela->addButton(2, TFTButton(tft, 0, 130, "A", OBJ_POS_RIGHT, BTN_TYPE_ARROW_DOWN, OBJ_SIZE_TEXT, []() { Serial.println("DOWN"); }));

    // Navigation
    tela->addButton(3, TFTButton(tft, 0, SCREEN_H - 50, "AAA", OBJ_POS_LEFT, BTN_TYPE_TENTH_MINUS10, OBJ_SIZE_TEXT, []() { Serial.println("-10"); }));
    tela->addButton(4, TFTButton(tft, 100, SCREEN_H - 50, "Z", OBJ_POS_NONE, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { Serial.println("-1"); }));
    tela->addButton(5, TFTButton(tft, SCREEN_W - 150, SCREEN_H - 50, "Z", OBJ_POS_NONE, BTN_TYPE_ARROW_RIGHT, OBJ_SIZE_TEXT, []() { Serial.println("+1"); }));
    tela->addButton(6, TFTButton(tft, 0, SCREEN_H - 50, "AAA", OBJ_POS_RIGHT, BTN_TYPE_TENTH_PLUS10, OBJ_SIZE_TEXT, []() { Serial.println("+10"); }));
}
void TelaIniciar(TFTScreen *tft, Screen *tela) {
    tela->addLabel(0, TFTLabel(tft, 0, 0, "INICIAR", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    tela->addButton(0, TFTButton(tft, 0, 0, " ", OBJ_POS_LEFT, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_SELECAO_INICIAL); }));
    tela->addButton(1, TFTButton(tft, 0, SCREEN_H / 2 - 50, "DO 1o CICLO", OBJ_POS_CENTER, BTN_TYPE_TEXT_GREEN, OBJ_SIZE_FIXED, []() {
                        Serial.println("Iniciar Operacoes...");
                        changeScreen(TELA_EM_CICLO);
                        // Fica circulando entre os ciclos até que seja clicado em PARAR
                    }));
    tela->addButton(2, TFTButton(tft, 0, SCREEN_H / 2 + 30, "SEL. CICLO", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { changeScreen(TELA_SELECIONAR_CICLO); }));
}
void TelaSelecionarCiclo(TFTScreen *tft, Screen *tela) {
    tela->addLabel(0, TFTLabel(tft, 0, 0, "SELECIONAR CICLO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 0, 80, "XXoC", OBJ_POS_CENTER, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    // Options
    tela->addButton(0, TFTButton(tft, 27, 75, "A", OBJ_POS_NONE, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { Serial.println("CICLO ANTERIOR"); }));
    tela->addButton(1, TFTButton(tft, 250, 75, "A", OBJ_POS_NONE, BTN_TYPE_ARROW_RIGHT, OBJ_SIZE_TEXT, []() { Serial.println("PROXIMO CICLO"); }));

    // removed due ARDUINO UNO memory limitation, put back with MEGA
    tela->addButton(2, TFTButton(tft, 0, 170, "INICIAR", OBJ_POS_CENTER, BTN_TYPE_TEXT_GREEN, OBJ_SIZE_FIXED, []() {
                        Serial.println("Iniciar Operacoes...");
                        changeScreen(TELA_EM_CICLO);
                        // Fica circulando entre os ciclos até que seja clicado em PARAR
                    }));
}

bool stoptelaEmCicloActive = false;
static bool telaEmCicloActive = false;
void TelaEmCiclo(TFTScreen *tft, Screen *tela) {
    telaEmCicloActive = true;
    // Title
     tela->addLabel(0, TFTLabel(tft, 24, 0, "STATUS:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 153, 0, statusTelaEmCiclo, OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    // Data
    tela->addLabel(2, TFTLabel(tft, 24, 48, "CICLO:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(3, TFTLabel(tft, 24, 84, "TEMPERATURA:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(4, TFTLabel(tft, 24, 120, "TEMPO RESTANTE:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(5, TFTLabel(tft, 220, 48, cicloTelaEmCiclo, OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(6, TFTLabel(tft, 220, 84, temperaturaTelaEmCiclo, OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    //removed due ARDUINO UNO memory limitation, put back with MEGA
    tela->addLabel(7, TFTLabel(tft, 220, 120, tempoTelaEmCiclo, OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addButton(0, TFTButton(tft, 0, 170, "PARAR", OBJ_POS_CENTER, BTN_TYPE_TEXT_RED, OBJ_SIZE_FIXED, []() { changeScreen(TELA_INICIAR); }));
    tela->draw();

    if (telaEmCicloActive) {
        unsigned long updateLabel = millis();
        long num = -100;
        while (1) {
            if (millis() > updateLabel + 250) {
                num%2 == 0 ? strcpy(statusTelaEmCiclo, "COLETANDO  ") : strcpy(statusTelaEmCiclo, "INS. PADRAO");
                itoa(num, cicloTelaEmCiclo, 10);
                itoa(num, temperaturaTelaEmCiclo, 10);
                itoa(num, tempoTelaEmCiclo, 10);
                tela->changeLabel(1, statusTelaEmCiclo);
                tela->changeLabel(5, cicloTelaEmCiclo);
                tela->changeLabel(6, temperaturaTelaEmCiclo);
                tela->changeLabel(7, tempoTelaEmCiclo);

                updateLabel = millis();
                num++;
            }

            if (readButtonsTela(tela) == 0) {
                stoptelaEmCicloActive = true;
            }
            if (stoptelaEmCicloActive) {
                stoptelaEmCicloActive = false;
                break;
            }
        }
    }
}

void TelaTeste(TFTScreen *tft, Screen *tela) {
    // tela->addLabel(0, TFTLabel(tft, 0, 0, "TESTE", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    // tela->addLabel(1, TFTLabel(tft, 0, 110, "XXoC", OBJ_POS_CENTER, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    // Options
    tela->addButton(0, TFTButton(tft, SCREEN_W / 2, 175, "PARAR", OBJ_POS_CENTER, BTN_TYPE_TEXT_RED, OBJ_SIZE_FIXED, []() { /*changeScreen(TELA_INICIAR);*/ }));
}
