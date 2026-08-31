#ifndef LEGAL_WIRE_H_REPLACEMENT
#define LEGAL_WIRE_H_REPLACEMENT

// ------------------------------------------------------------
// Legal Wire.h Replacement (CC BY-NC-ND)
// Minimal clean-room I²C Wire class stub.
// ------------------------------------------------------------

#include "Stream.h"   // your legal stub

class TwoWire : public Stream {
public:
    void begin() {}
    void begin(uint8_t address) { (void)address; }

    void beginTransmission(uint8_t address) { (void)address; }
    uint8_t endTransmission() { return 0; }

    size_t write(uint8_t b) override {
        (void)b;
        return 1;
    }

    int requestFrom(uint8_t address, uint8_t quantity) {
        (void)address; (void)quantity;
        return 0;
    }

    int read() override { return -1; }
};

static TwoWire Wire;

#endif
