#ifndef Ethernet_h
#define Ethernet_h

#include <Arduino.h>
#include <IPAddress.h>

struct Ethernet {
    IPAddress SubnetMask;
    uint16_t RetransmissionTimeout;
    byte RetransmissionCount;
    byte MACAddres[6];
    IPAddress Gateway;
    IPAddress DnsServer;
};

#endif //Ethernet