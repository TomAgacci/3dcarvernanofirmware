#ifndef LEGAL_SD_H_REPLACEMENT
#define LEGAL_SD_H_REPLACEMENT

// ------------------------------------------------------------
// Legal SD.h Replacement (CC BY-NC-ND)
// Minimal clean-room SD card API stub.
// ------------------------------------------------------------

#include "Arduino.h"
#include "Stream.h"

class File : public Stream {
public:
    bool available() { return false; }
    int read() override { return -1; }
    void close() {}
    size_t write(uint8_t b) override { (void)b; return 1; }
};

class SDClass {
public:
    bool begin(uint8_t csPin) {
        (void)csPin;
        return false;   // always fail (stub)
    }

    File open(const char* filename, uint8_t mode = 0) {
        (void)filename; (void)mode;
        return File();
    }
};

static SDClass SD;

#endif
