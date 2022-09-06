/*
    @author: Henrique Vilela
    @created: 2022-08-31
    @updated: 2022-09-03
    @version: 1.0
    @description
        Implements functions with main logic of project "Amostrador Automático"
*/

#include "Logic.h"

/* válvulas para os ciclos de 1 a 10 em ordem
VÁLVULA 1: 23 / VÁLVULA 2: 25 / VÁLVULA 3: 27
VÁLVULA 4: 29 / VÁLVULA 5: 31 / VÁLVULA 6: 33
VÁLVULA 7: 35 / VÁLVULA 8: 37 / VÁLVULA 9: 39
VÁLVULA 10: 41 */
const uint8_t valvPins[] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41};

/* Válvulas para acionamentos especiais
VX = 53 / VY = 49 / VZ = 47 / BOMBZ = 45 */
const uint8_t valvXPin = 45;
const uint8_t valvYPin = 47;
const uint8_t valvZPin = 49;
const uint8_t bombZPin = 53;

// salva o estado das válvulas
uint8_t valv[MAX_VALV];
uint8_t valvX;
uint8_t valvY;
uint8_t valvZ;
uint8_t bombZ;

void setupValvulas() {
    pinMode(valvXPin, OUTPUT);
    digitalWrite(valvXPin, DESLIGA);
    pinMode(valvYPin, OUTPUT);
    digitalWrite(valvYPin, DESLIGA);
    pinMode(valvZPin, OUTPUT);
    digitalWrite(valvZPin, DESLIGA);
    pinMode(bombZPin, OUTPUT);
    digitalWrite(bombZPin, DESLIGA);

    for (uint8_t i = 0; i < MAX_VALV; i++) {
        pinMode(valvPins[i], OUTPUT);
        digitalWrite(valvPins[i], DESLIGA);
    }
}

// função auxiliar
void atribuiValoresAsSaidas(uint8_t vx, uint8_t vy, uint8_t vz, uint8_t bz, uint8_t *valv) {
    digitalWrite(valvXPin, vx);
    digitalWrite(valvYPin, vy);
    digitalWrite(valvZPin, vz);
    digitalWrite(bombZPin, bz);

    for (uint8_t i = 0; i < MAX_VALV; i++) {
        digitalWrite(valvPins[i], valv[i]);
    }
}

void executaCiclo(uint8_t ciclo, Tarefa tarefa) {
    //ajusta valor do ciclo para o vetor
    uint8_t runningCiclo = ciclo - 1;

    // encerra função caso numero de ciclo seja incorreto ou tarefa inválida
    // (não deve ocorrer ao menos que haja algum erro no código)
    if (runningCiclo > MAX_VALV - 1 || runningCiclo < 0) {
        Serial.println("Ciclo fora do valor permitido!");
        return;
    }

    switch (tarefa) {
        case TAREFA_LIMPEZA:
            valvX = LIGA;
            valvY = DESLIGA;
            valvZ = LIGA;
            bombZ = LIGA;
            for (uint8_t i = 0; i < MAX_VALV; i++) {
                valv[i] = DESLIGA;
            }
            Serial.println("Exec. Ciclo: " + (String)ciclo + " - Tarefa: Limpeza");
            break;
        case TAREFA_INSERCAO:
            valvX = DESLIGA;
            valvY = LIGA;
            valvZ = DESLIGA;
            bombZ = DESLIGA;
            for (uint8_t i = 0; i < MAX_VALV; i++) {
                valv[i] = DESLIGA;
            }
            Serial.println("Exec. Ciclo: " + (String)ciclo + " - Tarefa: Inserção");
            break;
        case TAREFA_COLETA:
            valvX = DESLIGA;
            valvY = DESLIGA;
            valvZ = DESLIGA;
            bombZ = DESLIGA;
            for (uint8_t i = 0; i < MAX_VALV; i++) {
                i == runningCiclo ? valv[i] = LIGA : valv[i] = DESLIGA;
            }
            Serial.println("Exec. Ciclo: " + (String)ciclo + " - Tarefa: Coleta");
            break;
        default:
            break;
    }
    atribuiValoresAsSaidas(valvX, valvY, valvZ, bombZ, valv);
}

void resetValvulas(){
    valvX = DESLIGA;
    valvY = DESLIGA;
    valvZ = DESLIGA;
    bombZ = DESLIGA;
    for (uint8_t i = 0; i < MAX_VALV; i++) {
        valv[i] = DESLIGA;
    }
    atribuiValoresAsSaidas(valvX, valvY, valvZ, bombZ, valv);
}