
#include <Screen.h>

#pragma once

enum SCREEN_INDEX {
    TELA_TITULO,
    TELA_SELECAO_INICIAL,
    TELA_CONFIGURACAO,
    TELA_AGUARDANDO_TEMPERATURA,
    TELA_CONFIG_TEMPERATURA,
    TELA_CONFIG_CICLOS,
    TELA_INICIAR,
    TELA_SELECIONAR_CICLO,
    TELA_EM_CICLO
};

void initTela(TFTScreen *tft, Screen *tela, SCREEN_INDEX index);

void readButtonsTela(Screen *tela);

// CRIAÇÃO DAS TELAS
void TelaTitulo(TFTScreen *tft, Screen *tela);
void TelaSelecaoInicial(TFTScreen *tft, Screen *tela);
void TelaConfiguracao(TFTScreen *tft, Screen *tela);
void TelaAguardandoTemperatura(TFTScreen *tft, Screen *tela);
void TelaConfigTemperatura(TFTScreen *tft, Screen *tela);
void TelaConfigCiclos(TFTScreen *tft, Screen *tela);
void TelaIniciar(TFTScreen *tft, Screen *tela);
void TelaSelecionarCiclo(TFTScreen *tft, Screen *tela);
void TelaEmCiclo(TFTScreen *tft, Screen *tela);
