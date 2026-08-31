#ifndef LEGAL_TONE_H_REPLACEMENT
#define LEGAL_TONE_H_REPLACEMENT

// ------------------------------------------------------------
// Legal Tone.h Replacement (CC BY-NC-ND)
// Minimal clean-room tone/noTone stubs.
// ------------------------------------------------------------

#include "Arduino.h"

inline void tone(uint8_t pin, unsigned int frequency, unsigned long duration = 0) {
    (void)pin; (void)frequency; (void)duration;
    // no actual sound generation
}

inline void noTone(uint8_t pin) {
    (void)pin;
}

#endif
