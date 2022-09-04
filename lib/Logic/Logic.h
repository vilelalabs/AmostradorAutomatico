#pragma once

#include <Arduino.h>

// A Lógica de acionamento em barras de reles no geral é invertida (aciona com GND)
#define LIGA 1
#define DESLIGA 0

#define MAX_VALV 10

enum Tarefa {
    TAREFA_LIMPEZA,
    TAREFA_INSERCAO,
    TAREFA_COLETA
};

void setupValvulas();
void executaCiclo(uint8_t ciclo, Tarefa tarefa);
void resetValvulas();