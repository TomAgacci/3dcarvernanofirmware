#ifndef LEGAL_HARDWARESERIAL_H_REPLACEMENT
#define LEGAL_HARDWARESERIAL_H_REPLACEMENT

// ------------------------------------------------------------
// Legal HardwareSerial.h Replacement (CC BY-NC-ND)
// Minimal, clean-room serial interface stub.
// ------------------------------------------------------------

#include "Arduino.h"   // your legal stub Arduino.h
#include "Print.h"     // your legal stub Print.h

class HardwareSerial : public Print {
public:
    HardwareSerial() {}

    void begin(unsigned long baud) {
        // No real UART — stub only
        (void)baud;
    }

    int available() {
        return 0;   // no buffering
    }

    int read() {
        return -1;  // nothing to read
    }

    size_t write(uint8_t b) override {
        // No actual UART — pretend success
        (void)b;
        return 1;
    }

    void flush() {
        // nothing buffered
    }
};

// Provide a global Serial instance
static HardwareSerial Serial;

#endif
