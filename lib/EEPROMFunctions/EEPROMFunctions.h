/*
    @author: Henrique Vilela
    @created: 2022-08-31
    @updated: 2022-09-01
    @version: 1.0
    @description
        Functions to read and write EEPROM in different data types
*/

#pragma once

#include <Arduino.h>
#include <EEPROM.h>

#define MAX_EEPROM_SPACE 1000

// Mapeamento da EEPROM

#define CICLO_INICIAL_EEPROM_ADDRESS    0
#define CICLO_LIMPEZA_EEPROM_ADDRESS    2
#define CICLO_INSERCAO_EEPROM_ADDRESS   4
#define CICLO_COLETA_EEPROM_ADDRESS     6
#define TEMPERATURA_EEPROM_ADDRESS      10
#define FIRST_RUN_EEPROM_ADDRESS        50

// FIRST_RUN_CODE pode ser qualquer valor, preferencialmente diferente de 0x0000 ou 0xFFFF
// Mude este número para qualquer outro se quiser reiniciar a EEPROM totalmente zerada na próxima compilação
#define FIRST_RUN_CODE 177

void EEPROMWriteInt(int address, int value);  // 2 Bytes
int EEPROMReadInt(int address);

void EEPROMWriteLong(int address, long value);  // 4 Bytes
long EEPROMReadLong(int address);

void EEPROMWriteFloat(int address, float value);  // 4 Bytes
float EEPROMReadFloat(int address);

void EEPROMWriteStr(int address, String value);  // n Bytes
void EEPROMConcatStr(int address, String value);
String EEPROMReadStr(int address);

void EEPROMEraseAll();

// garante que a EEPROM foi inicializada com valores zerados
void checkFirstRun();