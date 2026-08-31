#ifndef LEGAL_USBAPI_H_REPLACEMENT
#define LEGAL_USBAPI_H_REPLACEMENT

// ------------------------------------------------------------
// Legal USBAPI.h Replacement (CC BY-NC-ND)
// Minimal USB API stub for compatibility.
// ------------------------------------------------------------

#include "Arduino.h"   // your legal stub
#include "Print.h"     // your legal stub

// Basic USB descriptor placeholders
#define USB_ENDPOINT_IN   0x80
#define USB_ENDPOINT_OUT  0x00

// Minimal USBDevice stub
class USBDevice {
public:
    void attach() {}
    void detach() {}
    bool configured() const { return false; }
};

// Global USB object stub
static USBDevice USBDeviceStub;

// Minimal CDC (serial over USB) stub
class SerialUSB : public Print {
public:
    void begin(unsigned long baud) { (void)baud; }
    int available() { return 0; }
    int read() { return -1; }
    size_t write(uint8_t b) override { (void)b; return 1; }
};

static SerialUSB SerialUSB;

#endif
