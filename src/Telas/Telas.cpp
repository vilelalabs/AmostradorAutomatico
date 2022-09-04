/*
updated: at least: 2022-08-24
*/

#include <EEPROMFunctions.h>
#include <Heater.h>
#include <Logic.h>
#include <Telas/Telas.h>
#include <TemperatureSensor.h>

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

        default:
            break;
    }
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
void clearScreen() {
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
    tela->addLabel(0, TFTLabel(tft, 0, 0, "AMOSTRADOR", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 50, 35, "AUTOMATICO", OBJ_POS_CENTER, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(2, TFTLabel(tft, 50, 70, "v. 1.0", OBJ_POS_CENTER, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    tela->addLabel(3, TFTLabel(tft, 0, SCREEN_H - 60, "Eng. Henrique Vilela", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(4, TFTLabel(tft, 50, SCREEN_H - 30, "hvilela.com", OBJ_POS_CENTER, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->draw();
}
//------------------------------------------------------------------------------------------------------------------------

void TelaSelecaoInicial(TFTScreen *tft, Screen *tela) {
    tela->addLabel(0, TFTLabel(tft, 0, 0, "AMOSTRADOR AUTOMATICO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addButton(0, TFTButton(tft, 0, SCREEN_H / 2 - 50, "CONFIGURACAO", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { changeScreen(TELA_CONFIGURACAO); }));
    tela->addButton(1, TFTButton(tft, 0, SCREEN_H / 2 + 30, "INICIAR", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { changeScreen(TELA_AGUARDANDO_TEMPERATURA); }));
    tela->draw();
}
//------------------------------------------------------------------------------------------------------------------------

void TelaConfiguracao(TFTScreen *tft, Screen *tela) {
    tela->addLabel(0, TFTLabel(tft, 0, 0, "CONFIGURACAO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addButton(0, TFTButton(tft, 0, 0, "<", OBJ_POS_LEFT, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_SELECAO_INICIAL); }));
    tela->addButton(1, TFTButton(tft, 0, SCREEN_H / 2 - 50, "TEMPERATURA", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { changeScreen(TELA_CONFIG_TEMPERATURA); }));
    tela->addButton(2, TFTButton(tft, 0, SCREEN_H / 2 + 30, "T. CICLOS", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { changeScreen(TELA_CONFIG_CICLOS); }));
    tela->draw();
}
//------------------------------------------------------------------------------------------------------------------------
bool stopTelaAguardandoTemperatura = false;
static bool telaAguardandoTemperaturaActive = false;
void TelaAguardandoTemperatura(TFTScreen *tft, Screen *tela) {
    char temperaturaAtualTelaAguardandoTemperatura[10] = "         ";
    char temperaturaProgramadaTelaAguardandoTemperatura[10] = "         ";

    telaAguardandoTemperaturaActive = true;
    // Title of Screen
    tela->addLabel(0, TFTLabel(tft, 0, 0, "AGUARDANDO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 0, 30, "TEMPERATURA", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    tela->addLabel(2, TFTLabel(tft, 90, 75, "ATUAL:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(3, TFTLabel(tft, 190, 75, "     ", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(4, TFTLabel(tft, 30, 115, "PROGRAMADA:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(5, TFTLabel(tft, 190, 115, "     ", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    tela->addButton(0, TFTButton(tft, 0, 170, "VOLTAR", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { changeScreen(TELA_SELECAO_INICIAL); }));
    tela->draw();

    if (telaAguardandoTemperaturaActive) {
        telaAguardandoTemperaturaActive = false;
        unsigned long updateLabel = millis();
        float temperaturaProgramada = EEPROMReadFloat(TEMPERATURA_EEPROM_ADDRESS);

        float temperaturaAtual = getTemperature();
        while (1) {
            if (millis() > updateLabel + 1000) {
                dtostrf(temperaturaProgramada, 2, 2, temperaturaProgramadaTelaAguardandoTemperatura);
                dtostrf(temperaturaAtual, 2, 2, temperaturaAtualTelaAguardandoTemperatura);
                tela->changeLabel(3, temperaturaAtualTelaAguardandoTemperatura);
                tela->changeLabel(5, temperaturaProgramadaTelaAguardandoTemperatura);

                updateLabel = millis();
                temperaturaAtual = getTemperature();
            }

            if (readButtonsTela(tela) == 0) {
                stopTelaAguardandoTemperatura = true;
            }

            // verifica se a resistencia de aquecimento deve ser liga/desligada
            activateHeater(temperaturaAtual, temperaturaProgramada);

            if (temperaturaAtual >= temperaturaProgramada) {  // comparação correta ">=", == apenas para testes
                activateHeater(getTemperature(), temperaturaProgramada);
                tela->changeLabel(0, (char *)"TEMPERATURA");
                tela->changeLabel(1, (char *)"  CORRETA! ");
                delay(2000);
                changeScreen(TELA_INICIAR);
                stopTelaAguardandoTemperatura = true;
            }
            if (stopTelaAguardandoTemperatura) {
                stopTelaAguardandoTemperatura = false;
                break;
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------

bool stopTelaConfigTemperatura = false;
static bool telaConfigTemperaturaActive = false;

void TelaConfigTemperatura(TFTScreen *tft, Screen *tela) {
    char temperaturaDesejadaTelaConfigTemperatura[10] = "         ";
    char temperaturaAtualTelaConfigTemperatura[10] = "         ";
    telaConfigTemperaturaActive = true;
    tela->addLabel(0, TFTLabel(tft, 0, 0, "TEMPERATURA", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    tela->addLabel(1, TFTLabel(tft, 60, 75, "ATUAL:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(2, TFTLabel(tft, 60, 120, "DESEJADA:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(4, TFTLabel(tft, SCREEN_W / 2 + 20, 75, "     ", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(5, TFTLabel(tft, SCREEN_W / 2 + 20, 120, "     ", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    // Back to previous screen
    tela->addButton(0, TFTButton(tft, 0, 0, " ", OBJ_POS_LEFT, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_CONFIGURACAO); }));

    // Navigation
    tela->addButton(1, TFTButton(tft, 0, SCREEN_H - 50, "-10", OBJ_POS_LEFT, BTN_TYPE_TENTH_MINUS10, OBJ_SIZE_TEXT, []() { Serial.println("-10"); }));
    tela->addButton(2, TFTButton(tft, 100, SCREEN_H - 50, "<", OBJ_POS_NONE, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { Serial.println("-1"); }));
    tela->addButton(3, TFTButton(tft, SCREEN_W - 150, SCREEN_H - 50, ">", OBJ_POS_NONE, BTN_TYPE_ARROW_RIGHT, OBJ_SIZE_TEXT, []() { Serial.println("+1"); }));
    tela->addButton(4, TFTButton(tft, 0, SCREEN_H - 50, "+10", OBJ_POS_RIGHT, BTN_TYPE_TENTH_PLUS10, OBJ_SIZE_TEXT, []() { Serial.println("+10"); }));
    tela->draw();

    if (telaConfigTemperaturaActive) {
        telaConfigTemperaturaActive = false;
        unsigned long updateLabel = millis();

        // variaveis usadas na tela
        float temperaturaAtual = getTemperature();
        float temperaturaDesejada = EEPROMReadFloat(TEMPERATURA_EEPROM_ADDRESS);

        while (1) {
            if (millis() > updateLabel + 250) {
                // conversoes das variaveis para string
                dtostrf(temperaturaAtual, 2, 2, temperaturaAtualTelaConfigTemperatura);
                dtostrf(temperaturaDesejada, 2, 2, temperaturaDesejadaTelaConfigTemperatura);
                // altera os labels
                tela->changeLabel(4, temperaturaAtualTelaConfigTemperatura);
                tela->changeLabel(5, temperaturaDesejadaTelaConfigTemperatura);

                updateLabel = millis();
                temperaturaAtual = getTemperature();
            }

            switch (readButtonsTela(tela)) {
                case 1:
                    temperaturaDesejada > 10 ? temperaturaDesejada -= 10 : 0;
                    EEPROMWriteFloat(TEMPERATURA_EEPROM_ADDRESS, temperaturaDesejada);
                    break;
                case 2:
                    temperaturaDesejada > 1 ? temperaturaDesejada -= 1 : 0;
                    EEPROMWriteFloat(TEMPERATURA_EEPROM_ADDRESS, temperaturaDesejada);
                    break;
                case 3:
                    temperaturaDesejada < 99 ? temperaturaDesejada += 1 : 0;
                    EEPROMWriteFloat(TEMPERATURA_EEPROM_ADDRESS, temperaturaDesejada);
                    break;
                case 4:
                    temperaturaDesejada < 90 ? temperaturaDesejada += 10 : 0;
                    EEPROMWriteFloat(TEMPERATURA_EEPROM_ADDRESS, temperaturaDesejada);
                    break;
                case 0:
                    stopTelaConfigTemperatura = true;
                    break;
                default:
                    break;
            }

            if (stopTelaConfigTemperatura) {
                stopTelaConfigTemperatura = false;
                break;
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------

bool stopTelaConfigCiclos = false;
static bool telaConfigCiclosActive = false;

void TelaConfigCiclos(TFTScreen *tft, Screen *tela) {
    char limpezaTelaConfigCiclos[5] = "    ";
    char insercaoTelaConfigCiclos[5] = "    ";
    char coletaTelaConfigCiclos[5] = "    ";

    telaConfigCiclosActive = true;
    // Title
    tela->addLabel(0, TFTLabel(tft, 0, 0, "TEMPO - CICLOS", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    // Data
    tela->addLabel(1, TFTLabel(tft, 60, 55, "LIMPEZA:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(2, TFTLabel(tft, 60, 90, "INSERCAO:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(3, TFTLabel(tft, 60, 125, "COLETA:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(4, TFTLabel(tft, SCREEN_W / 2 + 20, 55, "    ", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(5, TFTLabel(tft, SCREEN_W / 2 + 20, 90, "    ", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(6, TFTLabel(tft, SCREEN_W / 2 + 20, 125, "    ", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    // Back to previous screen
    tela->addButton(0, TFTButton(tft, 0, 0, " ", OBJ_POS_LEFT, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_CONFIGURACAO); }));

    // Options
    tela->addButton(1, TFTButton(tft, 0, 60, "A", OBJ_POS_RIGHT, BTN_TYPE_ARROW_UP, OBJ_SIZE_TEXT, []() { Serial.println("UP"); }));
    tela->addButton(2, TFTButton(tft, 0, 130, "A", OBJ_POS_RIGHT, BTN_TYPE_ARROW_DOWN, OBJ_SIZE_TEXT, []() { Serial.println("DOWN"); }));

    // Navigation
    tela->addButton(3, TFTButton(tft, 0, SCREEN_H - 50, "-10", OBJ_POS_LEFT, BTN_TYPE_TENTH_MINUS10, OBJ_SIZE_TEXT, []() { Serial.println("-10"); }));
    tela->addButton(4, TFTButton(tft, 100, SCREEN_H - 50, "<", OBJ_POS_NONE, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { Serial.println("-1"); }));
    tela->addButton(5, TFTButton(tft, SCREEN_W - 150, SCREEN_H - 50, ">", OBJ_POS_NONE, BTN_TYPE_ARROW_RIGHT, OBJ_SIZE_TEXT, []() { Serial.println("+1"); }));
    tela->addButton(6, TFTButton(tft, 0, SCREEN_H - 50, "+10", OBJ_POS_RIGHT, BTN_TYPE_TENTH_PLUS10, OBJ_SIZE_TEXT, []() { Serial.println("+10"); }));
    tela->draw();

    if (telaConfigCiclosActive) {
        telaConfigCiclosActive = false;
        unsigned long updateLabel = millis();

        // variaveis usadas na tela
        int limpezaTempo = EEPROMReadInt(CICLO_LIMPEZA_EEPROM_ADDRESS);
        int insercaoTempo = EEPROMReadInt(CICLO_INSERCAO_EEPROM_ADDRESS);
        int coletaTempo = EEPROMReadInt(CICLO_COLETA_EEPROM_ADDRESS);

        /* para efeito de selecao na tela*/
        int itemSelecionado = 0;  // 1 - limpeza, 2 - insercao, 3 - coleta
        tft->drawPointer(tela->getLabel(1).getX() - 10, tela->getLabel(1).getY());

        while (1) {
            if (millis() > updateLabel + 250) {
                // conversoes das variaveis para string
                itoa(limpezaTempo, limpezaTelaConfigCiclos, 10);
                itoa(insercaoTempo, insercaoTelaConfigCiclos, 10);
                itoa(coletaTempo, coletaTelaConfigCiclos, 10);

                // altera os labels
                tela->changeLabel(4, limpezaTelaConfigCiclos);
                tela->changeLabel(5, insercaoTelaConfigCiclos);
                tela->changeLabel(6, coletaTelaConfigCiclos);

                updateLabel = millis();
            }

            switch (readButtonsTela(tela)) {
                case 1:  // UP
                    if (itemSelecionado > 0) {
                        itemSelecionado--;
                        tft->getTFT().fillRect(tela->getLabel(1).getX() - 10, tela->getLabel(1).getY() + 15, 16, 86, BLACK);
                        tft->drawPointer(tela->getLabel(itemSelecionado + 1).getX() - 10, tela->getLabel(itemSelecionado + 1).getY());
                    }
                    break;

                case 2:  // DOWN
                    if (itemSelecionado < 2) {
                        itemSelecionado++;
                        tft->getTFT().fillRect(tela->getLabel(1).getX() - 10, tela->getLabel(1).getY() + 15, 16, 78, BLACK);
                        tft->drawPointer(tela->getLabel(itemSelecionado + 1).getX() - 10, tela->getLabel(itemSelecionado + 1).getY());
                    }

                    break;
                case 3:
                    switch (itemSelecionado) {
                        case 0:
                            limpezaTempo > 10 ? limpezaTempo -= 10 : 0;
                            EEPROMWriteInt(CICLO_LIMPEZA_EEPROM_ADDRESS, limpezaTempo);
                            break;
                        case 1:
                            insercaoTempo > 10 ? insercaoTempo -= 10 : 0;
                            EEPROMWriteInt(CICLO_INSERCAO_EEPROM_ADDRESS, insercaoTempo);
                            break;
                        case 2:
                            coletaTempo > 10 ? coletaTempo -= 10 : 0;
                            EEPROMWriteInt(CICLO_COLETA_EEPROM_ADDRESS, coletaTempo);
                            break;
                        default:
                            break;
                    }
                    break;
                case 4:
                    switch (itemSelecionado) {
                        case 0:
                            limpezaTempo > 1 ? limpezaTempo-- : 0;
                            EEPROMWriteInt(CICLO_LIMPEZA_EEPROM_ADDRESS, limpezaTempo);
                            break;
                        case 1:
                            insercaoTempo > 1 ? insercaoTempo-- : 0;
                            EEPROMWriteInt(CICLO_INSERCAO_EEPROM_ADDRESS, insercaoTempo);
                            break;
                        case 2:
                            coletaTempo > 1 ? coletaTempo-- : 0;
                            EEPROMWriteInt(CICLO_COLETA_EEPROM_ADDRESS, coletaTempo);
                            break;
                        default:
                            break;
                    }
                    break;
                case 5:
                    switch (itemSelecionado) {
                        case 0:
                            limpezaTempo < 99 ? limpezaTempo++ : 0;
                            EEPROMWriteInt(CICLO_LIMPEZA_EEPROM_ADDRESS, limpezaTempo);
                            break;
                        case 1:
                            insercaoTempo < 99 ? insercaoTempo++ : 0;
                            EEPROMWriteInt(CICLO_INSERCAO_EEPROM_ADDRESS, insercaoTempo);
                            break;
                        case 2:
                            coletaTempo < 99 ? coletaTempo++ : 0;
                            EEPROMWriteInt(CICLO_COLETA_EEPROM_ADDRESS, coletaTempo);
                            break;
                        default:
                            break;
                    }
                    break;
                case 6:
                    switch (itemSelecionado) {
                        case 0:
                            limpezaTempo < 90 ? limpezaTempo += 10 : 0;
                            EEPROMWriteInt(CICLO_LIMPEZA_EEPROM_ADDRESS, limpezaTempo);
                            break;
                        case 1:
                            insercaoTempo < 90 ? insercaoTempo += 10 : 0;
                            EEPROMWriteInt(CICLO_INSERCAO_EEPROM_ADDRESS, insercaoTempo);
                            break;
                        case 2:
                            coletaTempo < 90 ? coletaTempo += 10 : 0;
                            EEPROMWriteInt(CICLO_COLETA_EEPROM_ADDRESS, coletaTempo);
                            break;
                        default:
                            break;
                    }
                    break;
                case 0:
                    stopTelaConfigCiclos = true;
                    break;
                default:
                    break;
            }

            if (stopTelaConfigCiclos) {
                stopTelaConfigCiclos = false;
                break;
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------

void TelaIniciar(TFTScreen *tft, Screen *tela) {
    tela->addLabel(0, TFTLabel(tft, 0, 0, "INICIAR", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));

    tela->addButton(0, TFTButton(tft, 0, 0, " ", OBJ_POS_LEFT, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { changeScreen(TELA_SELECAO_INICIAL); }));
    tela->addButton(1, TFTButton(tft, 0, SCREEN_H / 2 - 50, "DO 1o CICLO", OBJ_POS_CENTER, BTN_TYPE_TEXT_GREEN, OBJ_SIZE_FIXED, []() {
                        Serial.println("Iniciar Operacoes...");
                        EEPROMWriteInt(CICLO_INICIAL_EEPROM_ADDRESS, 1);
                        changeScreen(TELA_EM_CICLO);
                    }));
    tela->addButton(2, TFTButton(tft, 0, SCREEN_H / 2 + 30, "SEL. CICLO", OBJ_POS_CENTER, BTN_TYPE_TEXT_BLUE, OBJ_SIZE_FIXED, []() { changeScreen(TELA_SELECIONAR_CICLO); }));
    tela->draw();

    unsigned long updateHeaterTime = millis();
    float temperaturaAtual = getTemperature();
    const float temperaturaProgramada = EEPROMReadFloat(TEMPERATURA_EEPROM_ADDRESS);
    while (1) {
        if (millis() > updateHeaterTime + 1000) {
            temperaturaAtual = getTemperature();
            updateHeaterTime = millis();
        }
        activateHeater(temperaturaAtual, temperaturaProgramada);

        const int button = readButtonsTela(tela);
        if (button == 0 || button == 1 || button == 2) {
            if (button == 0) {
                turnOffHeater();
            }
            break;
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------
bool stopTelaSelecionarCiclo = false;
static bool telaSelecionarCicloActive = false;
void TelaSelecionarCiclo(TFTScreen *tft, Screen *tela) {
    char limpezaTelaSelecionarCiclo[5] = "    ";

    telaSelecionarCicloActive = true;
    tela->addLabel(0, TFTLabel(tft, 0, 0, "SELECIONAR CICLO", OBJ_POS_CENTER, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, SCREEN_W / 2 - 25, 80, "    ", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));

    // Options
    tela->addButton(0, TFTButton(tft, 27, 75, "<", OBJ_POS_NONE, BTN_TYPE_ARROW_LEFT, OBJ_SIZE_TEXT, []() { Serial.println("CICLO ANTERIOR"); }));
    tela->addButton(1, TFTButton(tft, 250, 75, ">", OBJ_POS_NONE, BTN_TYPE_ARROW_RIGHT, OBJ_SIZE_TEXT, []() { Serial.println("PROXIMO CICLO"); }));

    tela->addButton(2, TFTButton(tft, 0, 170, "INICIAR", OBJ_POS_CENTER, BTN_TYPE_TEXT_GREEN, OBJ_SIZE_FIXED, []() {
                        Serial.println("Iniciar Operacoes...");
                        changeScreen(TELA_EM_CICLO);
                    }));
    tela->draw();

    if (telaSelecionarCicloActive) {
        telaSelecionarCicloActive = false;
        unsigned long updateLabel = millis();

        // variaveis usadas na tela
        int ciclo = EEPROMReadInt(CICLO_INICIAL_EEPROM_ADDRESS);

        unsigned long updateHeaterTime = millis();
        float temperaturaAtual = getTemperature();
        const float temperaturaProgramada = EEPROMReadFloat(TEMPERATURA_EEPROM_ADDRESS);

        while (1) {
            if (millis() > updateLabel + 250) {
                // conversoes das variaveis para string
                itoa(ciclo, limpezaTelaSelecionarCiclo, 10);
                // altera os labels
                tela->changeLabel(1, limpezaTelaSelecionarCiclo);

                updateLabel = millis();
            }
            if (millis() > updateHeaterTime + 1000) {
                temperaturaAtual = getTemperature();
                Serial.println("Testando temperaturas: ");
                Serial.println("temperaturaAtual: " + String(temperaturaAtual));
                Serial.println("temperaturaProgramada: " + String(temperaturaProgramada));
                updateHeaterTime = millis();
            }
            activateHeater(temperaturaAtual, temperaturaProgramada);

            switch (readButtonsTela(tela)) {
                case 0:  // LEFT
                    ciclo > 1 ? ciclo-- : 0;
                    EEPROMWriteInt(CICLO_INICIAL_EEPROM_ADDRESS, ciclo);
                    break;

                case 1:  // RIGHT
                    ciclo < 10 ? ciclo++ : 0;
                    EEPROMWriteInt(CICLO_INICIAL_EEPROM_ADDRESS, ciclo);
                    break;
                case 2:  // INICIAR
                    stopTelaSelecionarCiclo = true;
                    break;
                default:
                    break;
            }

            if (stopTelaSelecionarCiclo) {
                stopTelaSelecionarCiclo = false;
                break;
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------

bool stopTelaEmCiclo = false;
static bool telaEmCicloActive = false;
void TelaEmCiclo(TFTScreen *tft, Screen *tela) {
    char statusTelaEmCiclo[15] = "              ";
    char cicloTelaEmCiclo[5] = "    ";
    char temperaturaTelaEmCiclo[10] = "         ";
    char tempoTelaEmCiclo[5] = "    ";
    char buttonTelaEmCiclo[12] = "           ";
    telaEmCicloActive = true;
    bool stoppingAsked = false;
    // Title
    tela->addLabel(0, TFTLabel(tft, 24, 0, "STATUS:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(1, TFTLabel(tft, 153, 0, "           ", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    // Data
    tela->addLabel(2, TFTLabel(tft, 24, 48, "CICLO:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(3, TFTLabel(tft, 24, 84, "TEMPERATURA:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(4, TFTLabel(tft, 24, 120, "TEMPO RESTANTE:", OBJ_POS_NONE, LBL_TYPE_TITLE, OBJ_SIZE_TEXT));
    tela->addLabel(5, TFTLabel(tft, 220, 48, "    ", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(6, TFTLabel(tft, 220, 84, "    ", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addLabel(7, TFTLabel(tft, 220, 120, "    ", OBJ_POS_NONE, LBL_TYPE_DATA, OBJ_SIZE_TEXT));
    tela->addButton(0, TFTButton(tft, 0, 170, "  PARAR   ", OBJ_POS_CENTER, BTN_TYPE_TEXT_RED, OBJ_SIZE_FIXED, []() {}));
    tela->draw();

    // ATIVIDADE DA TELA "EM CICLO"
    if (telaEmCicloActive) {
        telaEmCicloActive = false;
        unsigned long updateLabel = millis();

        // variaveis usadas na tela
        char status[15] = "LIMPEZA";
        int ciclo = EEPROMReadInt(CICLO_INICIAL_EEPROM_ADDRESS);
        float temperatura = getTemperature();
        int tempoRestante = EEPROMReadInt(CICLO_LIMPEZA_EEPROM_ADDRESS);
        Tarefa tarefa = TAREFA_LIMPEZA;
        // inicia primeiro ciclo solicitado
        delay(2000);
        executaCiclo(ciclo, tarefa);
        const float temperaturaProgramada = EEPROMReadFloat(TEMPERATURA_EEPROM_ADDRESS);
        while (1) {
            activateHeater(getTemperature(), temperaturaProgramada);
            delay(100);
            if (millis() > updateLabel + 1000) {
                updateLabel = millis();
                // conversoes das variaveis para string

                strcpy(statusTelaEmCiclo, status);
                itoa(ciclo, cicloTelaEmCiclo, 10);
                dtostrf(temperatura, 2, 2, temperaturaTelaEmCiclo);
                itoa(tempoRestante - 1, tempoTelaEmCiclo, 10);
                stoppingAsked ? strcpy(buttonTelaEmCiclo, "PARANDO...") : strcpy(buttonTelaEmCiclo, "  PARAR   ");

                // altera os labels
                tela->changeLabel(1, statusTelaEmCiclo);
                tela->changeLabel(5, cicloTelaEmCiclo);
                tela->changeLabel(6, temperaturaTelaEmCiclo);
                tela->changeLabel(7, tempoTelaEmCiclo);
                tela->changeButton(0, buttonTelaEmCiclo);

                // update variables
                tempoRestante > 0 ? tempoRestante-- : 0;
                temperatura = getTemperature();
            }
            if (tempoRestante == 0) {
                if (tarefa == TAREFA_COLETA) {
                    ciclo < 10 ? ciclo++ : ciclo = 1;
                }
                switch (tarefa) {
                    case TAREFA_LIMPEZA:
                        strcpy(status, "INS.PADRAO");
                        tempoRestante = EEPROMReadInt(CICLO_INSERCAO_EEPROM_ADDRESS);
                        executaCiclo(ciclo, TAREFA_INSERCAO);
                        tarefa = TAREFA_INSERCAO;
                        break;
                    case TAREFA_INSERCAO:
                        strcpy(status, "EM COLETA");
                        tempoRestante = EEPROMReadInt(CICLO_COLETA_EEPROM_ADDRESS);
                        executaCiclo(ciclo, TAREFA_COLETA);

                        tarefa = TAREFA_COLETA;
                        break;
                    case TAREFA_COLETA:
                        if (!stoppingAsked) {
                            strcpy(status, "LIMPEZA");
                            tempoRestante = EEPROMReadInt(CICLO_LIMPEZA_EEPROM_ADDRESS);
                            executaCiclo(ciclo, TAREFA_LIMPEZA);
                            tarefa = TAREFA_LIMPEZA;
                            break;
                        } else {
                            stopTelaEmCiclo = true;
                            break;
                        }
                    default:
                        break;
                }
            }
            if (!stoppingAsked) {
                if (readButtonsTela(tela) == 0) {  // BOTAO PARAR
                    stoppingAsked = true;
                }
            }

            if (stopTelaEmCiclo) {
                resetValvulas();
                stoppingAsked = false;
                stopTelaEmCiclo = false;
                changeScreen(TELA_INICIAR);
                break;
            }
        }
    }
}
