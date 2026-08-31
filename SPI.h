#ifndef LEGAL_SPI_H_REPLACEMENT
#define LEGAL_SPI_H_REPLACEMENT

// ------------------------------------------------------------
// Legal SPI.h Replacement (CC BY-NC-ND)
// Minimal clean-room SPI class stub.
// ------------------------------------------------------------

#include "Arduino.h"   // your legal stub

class SPIClass {
public:
    void begin() {}

    void beginTransaction(int /*settings*/) {}

    uint8_t transfer(uint8_t data) {
        (void)data;
        return 0;   // no real SPI
    }

    void endTransaction() {}

    void end() {}
};

static SPIClass SPI;

#endif
