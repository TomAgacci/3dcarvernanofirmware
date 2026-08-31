#ifndef LEGAL_PRINT_H_REPLACEMENT
#define LEGAL_PRINT_H_REPLACEMENT

// ------------------------------------------------------------
// Legal Print.h Replacement (CC BY-NC-ND)
// Minimal Print class stub for compatibility.
// ------------------------------------------------------------

#include "Arduino.h"   // your legal stub Arduino.h

class Print {
public:
    virtual size_t write(uint8_t) { return 1; }

    size_t print(const char* s) {
        while (*s) write(*s++);
        return 1;
    }

    size_t print(long n) {
        char buf[16];
        ltoa(n, buf, 10);
        return print(buf);
    }

    size_t println(const char* s) {
        print(s);
        write('\n');
        return 1;
    }

    size_t println(long n) {
        print(n);
        write('\n');
        return 1;
    }
};

#endif
