#pragma once

#include <Arduino.h>

#define MAX_VALV 10

enum Tarefa {
    TAREFA_LIMPEZA,
    TAREFA_INSERCAO,
    TAREFA_COLETA
};

void setupValvulas();
void executaCiclo(uint8_t ciclo, Tarefa tarefa);
void resetValvulas();