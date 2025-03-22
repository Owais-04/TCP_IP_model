// bridge.cpp
#include "bridge.h"
#include <iostream>

void Bridge::learnMacAddress(const std::string& mac_source, int port) {
    macTable[mac_source] = port;
}

void Bridge::forwardFrame(const std::string& mac_dest, int incomingPort) {
    if (macTable.find(mac_dest) != macTable.end()) {
        std::cout << "Frame forwarded to port " << macTable[mac_dest] << " for MAC: " << mac_dest << std::endl;
    } else {
        std::cout << "Flooding frame to all ports except " << incomingPort << " for MAC: " << mac_dest << std::endl;
    }
}