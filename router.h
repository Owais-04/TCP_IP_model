#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "device.h"
#include "switch.h"

struct RouteEntry {
    std::string destinationIP;
    std::string nextHop;
    int metric;  // For dynamic routing
};

class Router {
public:
    std::string routerName;
    std::string routerIP;
    std::string macAddress;
    std::vector<RouteEntry> routingTable;
    std::unordered_map<std::string, std::string> arpTable;  // IP to MAC mapping
    Switch* connectedSwitch;  // For layer 2 functionality

    Router(std::string name, std::string ip, std::string mac);
    
    // Basic router operations
    void addRoute(std::string dest, std::string nextHop, int metric = 1);
    void removeRoute(std::string dest);
    void displayRoutingTable();
    
    // Packet handling with layer 2 integration
    void sendPacket(std::string sourceIP, std::string destinationIP, std::string data, std::string protocol = "Stop-and-Wait");
    void receivePacket(std::string sourceIP, std::string destinationIP, std::string data);
    
    // ARP operations
    void updateARPTable(std::string ip, std::string mac);
    std::string getMACFromIP(std::string ip);
    
    // Layer 2 integration
    void connectToSwitch(Switch* switchDevice);
    void setMacAddress(std::string mac) { macAddress = mac; }
    std::string getMacAddress() const { return macAddress; }
    
    // Getters
    std::string getRouterName() const { return routerName; }
    std::string getRouterIP() const { return routerIP; }
};

#endif
