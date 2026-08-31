#ifndef LEGAL_ETHERNET_H_REPLACEMENT
#define LEGAL_ETHERNET_H_REPLACEMENT

// ------------------------------------------------------------
// Legal Ethernet.h Replacement (CC BY-NC-ND)
// Minimal clean-room Ethernet API stub.
// ------------------------------------------------------------

#include "Client.h"   // your legal stub
#include "Server.h"   // your legal stub
#include "IPAddress.h"

class EthernetClass {
public:
    void begin(uint8_t* mac) { (void)mac; }
    void begin(uint8_t* mac, IPAddress ip) { (void)mac; (void)ip; }

    IPAddress localIP() const {
        return IPAddress(0,0,0,0);
    }
};

static EthernetClass Ethernet;

// Minimal EthernetClient stub
class EthernetClient : public Client {
public:
    int connect(IPAddress ip, uint16_t port) {
        (void)ip; (void)port;
        return 0;
    }
};

// Minimal EthernetServer stub
class EthernetServer : public Server {
public:
    EthernetServer(uint16_t port) { (void)port; }
    void begin() {}
};

#endif
