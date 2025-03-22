// bridge.h
#ifndef BRIDGE_H
#define BRIDGE_H

#include "device.h"
#include <unordered_map>

class Bridge : public Devices {
private:
    std::unordered_map<std::string, int> macTable; // MAC address forwarding table
public:
    void forwardFrame(const std::string& mac_dest, int incomingPort);
    void learnMacAddress(const std::string& mac_source, int port);
};

#endif // BRIDGE_H