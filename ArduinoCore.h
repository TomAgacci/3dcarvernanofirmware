#ifndef ARDUINO_CORE_CLEANROOM
#define ARDUINO_CORE_CLEANROOM

// ============================================================
//  ArduinoCore.h — Clean-Room Arduino Core Replacement
//  License: CC BY-NC-ND 4.0
//  Author: Maximillian
// ============================================================

// ------------------------------------------------------------
// Basic Types & Macros
// ------------------------------------------------------------
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long  uint32_t;

#define HIGH 0x1
#define LOW  0x0

#define INPUT         0x0
#define OUTPUT        0x1
#define INPUT_PULLUP  0x2

#define CHANGE 1
#define RISING 2
#define FALLING 3

// ------------------------------------------------------------
// Core Function Prototypes (Stubs)
// ------------------------------------------------------------
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
// Print Class (Stub)
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// HardwareSerial (Stub)
// ------------------------------------------------------------
class HardwareSerial : public Print {
public:
    void begin(unsigned long baud) { (void)baud; }
    int available() { return 0; }
    int read() { return -1; }
    size_t write(uint8_t b) override { (void)b; return 1; }
    void flush() {}
};

static HardwareSerial Serial;

// ------------------------------------------------------------
// Stream (Stub)
// ------------------------------------------------------------
class Stream : public Print {
public:
    virtual int available() { return 0; }
    virtual int read() { return -1; }
    virtual int peek() { return -1; }

    long parseInt() { return 0; }
    float parseFloat() { return 0.0f; }
};

// ------------------------------------------------------------
// pins_arduino (Stub)
// ------------------------------------------------------------
static const uint8_t D0 = 0, D1 = 1, D2 = 2, D3 = 3, D4 = 4, D5 = 5;
static const uint8_t D6 = 6, D7 = 7, D8 = 8, D9 = 9, D10 = 10;
static const uint8_t D11 = 11, D12 = 12, D13 = 13;

static const uint8_t A0 = 14, A1 = 15, A2 = 16, A3 = 17, A4 = 18, A5 = 19;

// ------------------------------------------------------------
// binary.h (Stub)
// ------------------------------------------------------------
#define B(x) ((int)strtol(#x, NULL, 2))

// ------------------------------------------------------------
// IPAddress (Stub)
// ------------------------------------------------------------
class IPAddress {
public:
    uint8_t bytes[4];
    IPAddress() { bytes[0]=bytes[1]=bytes[2]=bytes[3]=0; }
    IPAddress(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
        bytes[0]=a; bytes[1]=b; bytes[2]=c; bytes[3]=d;
    }
    uint8_t operator[](int i) const { return bytes[i]; }
    uint8_t& operator[](int i) { return bytes[i]; }
};

// ------------------------------------------------------------
// USBAPI (Stub)
// ------------------------------------------------------------
class USBDevice { public: void attach(){} void detach(){} bool configured()const{return false;} };
static USBDevice USBDeviceStub;

class SerialUSB : public Print {
public:
    void begin(unsigned long baud) { (void)baud; }
    int available() { return 0; }
    int read() { return -1; }
    size_t write(uint8_t b) override { (void)b; return 1; }
};
static SerialUSB SerialUSB;

// ------------------------------------------------------------
// Client (Stub)
// ------------------------------------------------------------
class Client : public Stream {
public:
    virtual int connect(const char* host, uint16_t port) { (void)host; (void)port; return 0; }
    virtual void stop() {}
    virtual uint8_t connected() { return 0; }
};

// ------------------------------------------------------------
// Server (Stub)
// ------------------------------------------------------------
class Server : public Print {
public:
    virtual void begin() {}
    virtual void stop() {}
    size_t write(uint8_t b) override { (void)b; return 1; }
};

// ------------------------------------------------------------
// Wire (I2C Stub)
// ------------------------------------------------------------
class TwoWire : public Stream {
public:
    void begin() {}
    void begin(uint8_t address) { (void)address; }
    void beginTransmission(uint8_t address) { (void)address; }
    uint8_t endTransmission() { return 0; }
    size_t write(uint8_t b) override { (void)b; return 1; }
    int requestFrom(uint8_t address, uint8_t qty) { (void)address; (void)qty; return 0; }
};
static TwoWire Wire;

// ------------------------------------------------------------
// SPI (Stub)
// ------------------------------------------------------------
class SPIClass {
public:
    void begin() {}
    uint8_t transfer(uint8_t data) { (void)data; return 0; }
};
static SPIClass SPI;

// ------------------------------------------------------------
// Ethernet (Stub)
// ------------------------------------------------------------
class EthernetClass {
public:
    void begin(uint8_t* mac) { (void)mac; }
    IPAddress localIP() const { return IPAddress(0,0,0,0); }
};
static EthernetClass Ethernet;

// ------------------------------------------------------------
// WiFi (Stub)
// ------------------------------------------------------------
class WiFiClass {
public:
    int begin(const char* ssid, const char* pass) { (void)ssid; (void)pass; return 0; }
    IPAddress localIP() const { return IPAddress(0,0,0,0); }
};
static WiFiClass WiFi;

// ------------------------------------------------------------
// SD (Stub)
// ------------------------------------------------------------
class File : public Stream {
public:
    int read() override { return -1; }
    void close() {}
};

class SDClass {
public:
    bool begin(uint8_t csPin) { (void)csPin; return false; }
    File open(const char* filename, uint8_t mode=0) { (void)filename; (void)mode; return File(); }
};
static SDClass SD;

// ------------------------------------------------------------
// Servo (Stub)
// ------------------------------------------------------------
class Servo {
public:
    uint8_t pin = 255;
    int angle = 0;
    uint8_t attach(uint8_t p){ pin=p; return p; }
    void detach(){ pin=255; }
    void write(int a){ angle=a; }
    int read() const { return angle; }
};

// ------------------------------------------------------------
// SoftwareSerial (Stub)
// ------------------------------------------------------------
class SoftwareSerial : public Stream {
public:
    SoftwareSerial(uint8_t rx, uint8_t tx){ (void)rx; (void)tx; }
    void begin(unsigned long baud){ (void)baud; }
    int read() override { return -1; }
    size_t write(uint8_t b) override { (void)b; return 1; }
};

// ------------------------------------------------------------
// EEPROM (Stub)
// ------------------------------------------------------------
class EEPROMClass {
public:
    uint8_t read(int address){ (void)address; return 0; }
    void write(int address, uint8_t value){ (void)address; (void)value; }
};
static EEPROMClass EEPROM;

// ------------------------------------------------------------
// Keyboard (Stub)
// ------------------------------------------------------------
class Keyboard_ : public Print {
public:
    void begin() {}
    void end() {}
    size_t write(uint8_t k) override { (void)k; return 1; }
};
static Keyboard_ Keyboard;

// ------------------------------------------------------------
// Mouse (Stub)
// ------------------------------------------------------------
class Mouse_ {
public:
    void begin() {}
    void end() {}
    void click(uint8_t b=1){ (void)b; }
    void move(int x,int y,int w=0){ (void)x; (void)y; (void)w; }
};
static Mouse_ Mouse;

// ------------------------------------------------------------
// Tone (Stub)
// ------------------------------------------------------------
inline void tone(uint8_t pin, unsigned int freq, unsigned long dur=0){
    (void)pin; (void)freq; (void)dur;
}
inline void noTone(uint8_t pin){ (void)pin; }

#endif
