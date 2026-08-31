#ifndef LEGAL_SERVER_H_REPLACEMENT
#define LEGAL_SERVER_H_REPLACEMENT

// ------------------------------------------------------------
// Legal Server.h Replacement (CC BY-NC-ND)
// Minimal clean-room Server class stub.
// ------------------------------------------------------------

#include "Print.h"   // your legal stub

class Server : public Print {
public:
    virtual void begin() {}

    virtual void stop() {}

    virtual size_t write(uint8_t b) override {
        (void)b;
        return 1;
    }
};

#endif
