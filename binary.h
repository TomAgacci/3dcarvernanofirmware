#ifndef LEGAL_BINARY_H_REPLACEMENT
#define LEGAL_BINARY_H_REPLACEMENT

// ------------------------------------------------------------
// Legal binary.h Replacement (CC BY-NC-ND)
// Minimal binary constant helper.
// ------------------------------------------------------------

// Convert a binary literal (e.g., B1010) into an integer.
// This is a simple macro, not copyrighted logic.
#define B(x) ((int)strtol(#x, NULL, 2))

#endif
