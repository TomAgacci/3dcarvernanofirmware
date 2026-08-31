#ifndef LEGAL_IPADDRESS_H_REPLACEMENT
#define LEGAL_IPADDRESS_H_REPLACEMENT

// ------------------------------------------------------------
// Legal IPAddress.h Replacement (CC BY-NC-ND)
// Minimal IPAddress class stub.
// ------------------------------------------------------------

#include "Arduino.h"   // your legal stub

class IPAddress {
public:
    uint8_t bytes[4];

    IPAddress() {
        bytes[0] = bytes[1] = bytes[2] = bytes[3] = 0;
    }

    IPAddress(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
        bytes[0] = a;
        bytes[1] = b;
        bytes[2] = c;
        bytes[3] = d;
    }

    uint8_t operator[](int index) const {
        return bytes[index];
    }

    uint8_t& operator[](int index) {
        return bytes[index];
    }
};

#endif
