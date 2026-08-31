#ifndef LEGAL_WIFI_H_REPLACEMENT
#define LEGAL_WIFI_H_REPLACEMENT

// ------------------------------------------------------------
// Legal WiFi.h Replacement (CC BY-NC-ND)
// Minimal clean-room WiFi API stub.
// ------------------------------------------------------------

#include "Client.h"
#include "Server.h"
#include "IPAddress.h"

class WiFiClass {
public:
    int begin(const char* ssid, const char* pass) {
        (void)ssid; (void)pass;
        return 0;   // always fail (stub)
    }

    IPAddress localIP() const {
        return IPAddress(0,0,0,0);
    }

    int status() const {
        return 0;   // WL_IDLE_STATUS equivalent
    }
};

static WiFiClass WiFi;

// Minimal WiFiClient stub
class WiFiClient : public Client {
public:
    int connect(const char* host, uint16_t port) override {
        (void)host; (void)port;
        return 0;
    }
};

// Minimal WiFiServer stub
class WiFiServer : public Server {
public:
    WiFiServer(uint16_t port) { (void)port; }
    void begin() {}
};

#endif
