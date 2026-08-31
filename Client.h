#ifndef LEGAL_CLIENT_H_REPLACEMENT
#define LEGAL_CLIENT_H_REPLACEMENT

// ------------------------------------------------------------
// Legal Client.h Replacement (CC BY-NC-ND)
// Minimal clean-room Client class stub.
// ------------------------------------------------------------

#include "Stream.h"   // your legal stub

class Client : public Stream {
public:
    virtual int connect(const char* host, uint16_t port) {
        (void)host; (void)port;
        return 0;   // always fail (stub)
    }

    virtual void stop() {}

    virtual uint8_t connected() {
        return 0;   // never connected
    }

    virtual size_t write(uint8_t b) override {
        (void)b;
        return 1;
    }
};

#endif
