/*
    @author: Henrique Vilela
    @created: 2022-08-31
    @updated: 2022-09-01
    @version: 1.0
    @description
        Implements EEPROM read and write data functions
*/

#include "EEPROMFunctions.h"

byte varByte;
int varInt;
long varLong;
String varString;

void EEPROMWriteInt(int address, int value) {
    EEPROM.write(address, highByte(value));
    EEPROM.write(address + 1, lowByte(value));
}

int EEPROMReadInt(int address) {
    return word(EEPROM.read(address), EEPROM.read(address + 1));
}

void EEPROMWriteLong(int address, long value) {
    EEPROM.write(address, (value & 0xFF));
    EEPROM.write(address + 1, ((value >> 8) & 0xFF));
    EEPROM.write(address + 2, ((value >> 16) & 0xFF));
    EEPROM.write(address + 3, ((value >> 24) & 0xFF));
}

long EEPROMReadLong(int address) {
    long pos4 = EEPROM.read(address);
    long pos3 = EEPROM.read(address + 1);
    long pos2 = EEPROM.read(address + 2);
    long pos1 = EEPROM.read(address + 3);

    return ((pos4 << 0) & 0xFF) + ((pos3 << 8) & 0xFFFF) + ((pos2 << 16) & 0xFFFFFF) + ((pos1 << 24) & 0xFFFFFFFF);
}

void EEPROMWriteFloat(int address, float value) {
    byte* p = (byte*)(void*)&value;
    for (unsigned i = 0; i < sizeof(value); i++)
        EEPROM.write(address++, *p++);
}

float EEPROMReadFloat(int address) {
    float output;
    byte* p = (byte*)(void*)&output;
    for (unsigned i = 0; i < sizeof(output); i++)    
        *p++ = EEPROM.read(address++);
    return output;
}


void EEPROMWriteStr(int address, String value) {
    unsigned addressPosition;

    for (addressPosition = 0; addressPosition < value.length(); addressPosition++) {
        EEPROM.write(address + addressPosition, value.charAt(addressPosition));

        if (addressPosition >= MAX_EEPROM_SPACE) {
            break;
        }
    }

    if (addressPosition < MAX_EEPROM_SPACE) {
        EEPROM.write(address + addressPosition, (char)0);
    }
}

void EEPROMConcatStr(int address, String value) {
    unsigned addressPosition;
    char readByte;
    bool nullFound = false;
    unsigned strPos = 0;

    for (addressPosition = 0; addressPosition < MAX_EEPROM_SPACE; addressPosition++) {
        if (!nullFound) {
            readByte = EEPROM.read(address + addressPosition);

            if (readByte == (char)0) {
                nullFound = true;
            }
        }

        if (nullFound) {
            EEPROM.write(address + addressPosition, value.charAt(strPos));
            strPos++;

            if ((strPos + 1) > value.length()) {
                EEPROM.write(address + addressPosition + 1, (char)0);
                break;
            }
        }
    }
}

String EEPROMReadStr(int address) {
    String readStr = "";
    char readByte;

    int readAddress = address;

    do {
        readByte = EEPROM.read(readAddress);
        readStr += readByte;
        readAddress++;
    } while ((readByte != (char)0) && (readAddress < (address + MAX_EEPROM_SPACE)));

    return readStr;
}

void EEPROMEraseAll() {
    for (int addressPosition = 0; addressPosition < MAX_EEPROM_SPACE; addressPosition++) {
        EEPROM.write(addressPosition, 0);
    }
}

//----------------------------------------------
void checkFirstRun(){
    if (EEPROMReadInt(FIRST_RUN_EEPROM_ADDRESS) != FIRST_RUN_CODE) {
        Serial.println("Detected first run, initializing EEPROM");
        EEPROMEraseAll();
        EEPROMWriteInt(FIRST_RUN_EEPROM_ADDRESS, FIRST_RUN_CODE);

        // Set default values
        EEPROMWriteInt(CICLO_INICIAL_EEPROM_ADDRESS, 1);
        EEPROMWriteInt(CICLO_LIMPEZA_EEPROM_ADDRESS, 5);
        EEPROMWriteInt(CICLO_INSERCAO_EEPROM_ADDRESS, 5);
        EEPROMWriteInt(CICLO_COLETA_EEPROM_ADDRESS, 5);
        EEPROMWriteFloat(TEMPERATURA_EEPROM_ADDRESS, 50.0);

        Serial.println("Done! Continuing startup...");
    }
}