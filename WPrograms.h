#ifndef LEGAL_WPROGRAM_H_REPLACEMENT
#define LEGAL_WPROGRAM_H_REPLACEMENT

// ------------------------------------------------------------
// Legal WProgram.h Replacement (CC BY-NC-ND)
// Minimal compatibility layer for legacy Arduino sketches.
// ------------------------------------------------------------

#include "Arduino.h"   // your legal stub Arduino.h

// Provide basic typedefs commonly expected
typedef unsigned char  byte;
typedef unsigned short word;

// Provide minimal macros
#define bitRead(value, bit)    (((value) >> (bit)) & 0x01)
#define bitSet(value, bit)     ((value) |= (1UL << (bit)))
#define bitClear(value, bit)   ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) \
    (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#endif
