#ifndef LEGAL_STREAM_H_REPLACEMENT
#define LEGAL_STREAM_H_REPLACEMENT

// ------------------------------------------------------------
// Legal Stream.h Replacement (CC BY-NC-ND)
// Minimal clean-room Stream class stub.
// Provides read/parse helpers without copyrighted logic.
// ------------------------------------------------------------

#include "Print.h"   // your legal stub Print.h

class Stream : public Print {
public:
    virtual int available() { return 0; }
    virtual int read() { return -1; }
    virtual int peek() { return -1; }

    // Basic parseInt stub (no real parsing)
    long parseInt() {
        // No buffer — always return 0
        return 0;
    }

    // Basic parseFloat stub
    float parseFloat() {
        return 0.0f;
    }

    // Basic readStringUntil stub
    String readStringUntil(char terminator) {
        (void)terminator;
        return String("");
    }
};

#endif
