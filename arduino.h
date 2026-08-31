#ifndef LEGAL_ARDUINO_H_REPLACEMENT
#define LEGAL_ARDUINO_H_REPLACEMENT

// ------------------------------------------------------------
// Legal Arduino.h Replacement (CC BY-NC-ND)
// Provides minimal declarations required for compilation.
// No copyrighted source code included.
// ------------------------------------------------------------

// Basic types
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long  uint32_t;

// Logic levels
#define HIGH 0x1
#define LOW  0x0

// Pin modes
#define INPUT         0x0
#define OUTPUT        0x1
#define INPUT_PULLUP  0x2

// Interrupt modes
#define CHANGE 1
#define RISING 2
#define FALLING 3

// Core Arduino function prototypes
extern "C" {
    void pinMode(uint8_t pin, uint8_t mode);
    void digitalWrite(uint8_t pin, uint8_t val);
    int  digitalRead(uint8_t pin);
    int  analogRead(uint8_t pin);

    void delay(unsigned long ms);
    void delayMicroseconds(unsigned int us);
    unsigned long millis();
    unsigned long micros();

    void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode);
    uint8_t digitalPinToInterrupt(uint8_t pin);
}

// ------------------------------------------------------------
// Minimal Serial stub
// ------------------------------------------------------------
class HardwareSerial {
public:
    void begin(unsigned long baud) {}
    int available() { return 0; }
    int read() { return -1; }
    void print(const char*) {}
    void print(long) {}
    void println(const char*) {}
    void println(long) {}
    void write(uint8_t) {}
};

static HardwareSerial Serial;

#endif
