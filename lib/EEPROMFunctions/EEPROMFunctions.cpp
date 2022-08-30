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

void EEPROMWriteStr(int address, String value) {
    int addressPosition;

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
    int addressPosition;
    char readByte;
    bool nullFound = false;
    int strPos = 0;

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
    if (EEPROMReadInt(50) != FIRST_RUN_CODE) {
        Serial.println("Detected first run, initializing EEPROM");
        EEPROMEraseAll();
        EEPROMWriteInt(50, FIRST_RUN_CODE);
        Serial.println("Done! Continuing startup...");
    }
}