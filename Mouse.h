#ifndef LEGAL_MOUSE_H_REPLACEMENT
#define LEGAL_MOUSE_H_REPLACEMENT

// ------------------------------------------------------------
// Legal Mouse.h Replacement (CC BY-NC-ND)
// Minimal clean-room Mouse API stub.
// ------------------------------------------------------------

class Mouse_ {
public:
    void begin() {}
    void end() {}

    void click(uint8_t button = 1) { (void)button; }
    void press(uint8_t button = 1) { (void)button; }
    void release(uint8_t button = 1) { (void)button; }
    void move(int x, int y, int wheel = 0) {
        (void)x; (void)y; (void)wheel;
    }
};

static Mouse_ Mouse;

#endif
