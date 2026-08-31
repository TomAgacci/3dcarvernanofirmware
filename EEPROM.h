#ifndef LEGAL_EEPROM_H_REPLACEMENT
#define LEGAL_EEPROM_H_REPLACEMENT

// ------------------------------------------------------------
// Legal EEPROM.h Replacement (CC BY-NC-ND)
// Minimal clean-room EEPROM stub.
// ------------------------------------------------------------

#include "Arduino.h"

class EEPROMClass {
public:
    uint8_t read(int address) {
        (void)address;
        return 0;   // always return 0 (stub)
    }

    void write(int address, uint8_t value) {
        (void)address;
        (void)value;
        // no actual storage
    }

    void update(int address, uint8_t value) {
        write(address, value);
    }
};

static EEPROMClass EEPROM;

#endif
