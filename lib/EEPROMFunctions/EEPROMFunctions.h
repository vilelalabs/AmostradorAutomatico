#pragma once

#include <Arduino.h>
#include <EEPROM.h>

#define MAX_EEPROM_SPACE 1000

// FIRST_RUN_CODE pode ser qualquer valor, preferencialmente diferente de 0x0000 ou 0xFFFF
#define FIRST_RUN_CODE 183  // 0x00B7

void EEPROMWriteInt(int address, int value);  // 2 Bytes
int EEPROMReadInt(int address);

void EEPROMWriteLong(int address, long value);  // 4 Bytes
long EEPROMReadLong(int address);

void EEPROMWriteStr(int address, String value);  // n Bytes
void EEPROMConcatStr(int address, String value);
String EEPROMReadStr(int address);

void EEPROMEraseAll();

// garante que a EEPROM foi inicializada com valores zerados
void checkFirstRun();