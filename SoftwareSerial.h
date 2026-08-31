#ifndef LEGAL_SOFTWARESERIAL_H_REPLACEMENT
#define LEGAL_SOFTWARESERIAL_H_REPLACEMENT

// ------------------------------------------------------------
// Legal SoftwareSerial.h Replacement (CC BY-NC-ND)
// Minimal clean-room SoftwareSerial stub.
// ------------------------------------------------------------

#include "Stream.h"

class SoftwareSerial : public Stream {
public:
    SoftwareSerial(uint8_t rx, uint8_t tx) {
        (void)rx; (void)tx;
    }

    void begin(unsigned long baud) {
        (void)baud;
    }

    int available() override {
        return 0;
    }

    int read() override {
        return -1;
    }

    int peek() override {
        return -1;
    }

    size_t write(uint8_t b) override {
        (void)b;
        return 1;
    }
};

#endif
