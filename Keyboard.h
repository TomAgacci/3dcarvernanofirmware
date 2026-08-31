#ifndef LEGAL_KEYBOARD_H_REPLACEMENT
#define LEGAL_KEYBOARD_H_REPLACEMENT

// ------------------------------------------------------------
// Legal Keyboard.h Replacement (CC BY-NC-ND)
// Minimal clean-room Keyboard API stub.
// ------------------------------------------------------------

#include "Print.h"

class Keyboard_ : public Print {
public:
    void begin() {}
    void end() {}

    size_t write(uint8_t k) override {
        (void)k;
        return 1;
    }

    void press(uint8_t k) { (void)k; }
    void release(uint8_t k) { (void)k; }
    void releaseAll() {}
};

static Keyboard_ Keyboard;

#endif
