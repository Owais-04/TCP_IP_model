#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include "router.h"
#include "switch.h"
using namespace std;

Router::Router(string name, string ip, string mac) {
    routerName = name;
    routerIP = ip;
    macAddress = mac;
    connectedSwitch = nullptr;
}

void Router::addRoute(string dest, string nextHop, int metric) {
    auto it = find_if(routingTable.begin(), routingTable.end(),
        [&dest](const RouteEntry& entry) { return entry.destinationIP == dest; });
    
    if (it != routingTable.end()) {
        it->nextHop = nextHop;
        it->metric = metric;
    } else {
        routingTable.push_back({dest, nextHop, metric});
    }
}

void Router::removeRoute(string dest) {
    routingTable.erase(
        remove_if(routingTable.begin(), routingTable.end(),
            [&dest](const RouteEntry& entry) { return entry.destinationIP == dest; }),
        routingTable.end()
    );
}

void Router::displayRoutingTable() {
    cout << "\nRouting Table for " << routerName << " (" << routerIP << "):\n";
    cout << "Destination\t\tNext Hop\t\tMetric\n";
    cout << "------------------------------------------------\n";
    
    for (const auto& entry : routingTable) {
        cout << entry.destinationIP << "\t\t"
              << entry.nextHop << "\t\t"
              << entry.metric << "\n";
    }
}

void Router::connectToSwitch(Switch* switchDevice) {
    connectedSwitch = switchDevice;
    cout << "Router " << routerName << " connected to switch\n";
}

bool ipInSubnet(const std::string& ip, const std::string& subnet) {
    size_t slash = subnet.find('/');
    if (slash == std::string::npos) return false;
    std::string subnetBase = subnet.substr(0, slash);
    int prefix = std::stoi(subnet.substr(slash + 1));
    if (prefix != 24) return false; // Only handle /24 for now

    // Compare first 3 octets
    int dots = 0;
    for (size_t i = 0; i < ip.size() && i < subnetBase.size(); ++i) {
        if (ip[i] != subnetBase[i]) {
            return false;
        }
        if (ip[i] == '.') {
            dots++;
            if (dots == 3) break;
        }
    }
    return true;
}

void Router::sendPacket(string sourceIP, string destinationIP, string data, string protocol) {
    cout << "\nRouter " << routerName << " processing packet:\n";
    cout << "From: " << sourceIP << " To: " << destinationIP << "\n";
    cout << "Data: " << data << "\n";
    cout << "Protocol: " << protocol << "\n";

    auto it = find_if(routingTable.begin(), routingTable.end(),
        [&destinationIP](const RouteEntry& entry) {
            return ipInSubnet(destinationIP, entry.destinationIP);
        });

    if (it != routingTable.end()) {
        string nextHopMAC = getMACFromIP(it->nextHop);
        if (!nextHopMAC.empty()) {
            cout << "Forwarding packet to " << it->nextHop 
                      << " (MAC: " << nextHopMAC << ")\n";
            
            if (connectedSwitch) {
                cout << "Using " << protocol << " protocol for transmission\n";
                connectedSwitch->applyAccessControl(protocol, macAddress, nextHopMAC, data);
            } else {
                cout << "No switch connected for layer 2 transmission\n";
            }
        } else {
            cout << "ARP resolution needed for " << it->nextHop << "\n";
        }
    } else {
        cout << "No route to destination " << destinationIP << "\n";
    }
}

void Router::receivePacket(string sourceIP, string destinationIP, string data) {
    cout << "\nRouter " << routerName << " received packet:\n";
    cout << "From: " << sourceIP << " To: " << destinationIP << "\n";
    
    updateARPTable(sourceIP, "MAC_FROM_PACKET");
    
    if (destinationIP == routerIP) {
        cout << "Packet received by router " << routerName << "\n";
        return;
    }
    
    sendPacket(sourceIP, destinationIP, data, "Stop-and-Wait");
}

void Router::updateARPTable(string ip, string mac) {
    arpTable[ip] = mac;
}

string Router::getMACFromIP(string ip) {
    auto it = arpTable.find(ip);
    if (it != arpTable.end()) {
        return it->second;
    }
    return "";
}

void static_routing() {
    cout << "=== Static Routing Simulation ===\n";

    // Create switch for layer 2 functionality
    Switch networkSwitch;
    networkSwitch.setDevice("00:3A:4B:5C:6D:7E");

    // Create routers
    Router R1("R1", "192.168.1.1", "00:1A:2B:3C:4D:5E");
    Router R2("R2", "192.168.1.2", "00:1B:3C:4D:5E:6F");

    // Connect routers to switch
    R1.connectToSwitch(&networkSwitch);
    R2.connectToSwitch(&networkSwitch);

    // Add routes
    R1.addRoute("192.168.1.2", "192.168.1.2", 1);
    R2.addRoute("192.168.1.1", "192.168.1.1", 1);

    // Display routing tables
    R1.displayRoutingTable();
    R2.displayRoutingTable();

    // Simulate packet transmission
    string sourceIP, destIP, data, protocol;
    cout << "Enter source IP: ";
    cin >> sourceIP;
    cout << "Enter destination IP: ";
    cin >> destIP;
    cout << "Enter data to send: ";
    cin.ignore();
    getline(cin, data);
    cout << "Choose protocol (Stop-and-Wait/Selective-Repeat): ";
    getline(cin, protocol);

    R1.sendPacket(sourceIP, destIP, data, protocol);
}

void dynamic_routing() {
    cout << "=== Dynamic Routing Simulation ===\n";
    // Create switch for layer 2 functionality
    Switch networkSwitch;
    networkSwitch.setDevice("00:3A:4B:5C:6D:7E");

    // Create routers
    Router R1("R1", "192.168.1.1", "00:1A:2B:3C:4D:5E");
    Router R2("R2", "192.168.1.2", "00:1B:3C:4D:5E:6F");
    Router R3("R3", "192.168.1.3", "00:1C:3D:4E:5F:6G");

    // Connect routers to switch
    R1.connectToSwitch(&networkSwitch);
    R2.connectToSwitch(&networkSwitch);
    R3.connectToSwitch(&networkSwitch);

    // Add initial routes
    R1.addRoute("192.168.1.2", "192.168.1.2", 1);
    R1.addRoute("192.168.1.3", "192.168.1.3", 2);
    R2.addRoute("192.168.1.1", "192.168.1.1", 1);
    R2.addRoute("192.168.1.3", "192.168.1.3", 1);
    R3.addRoute("192.168.1.1", "192.168.1.1", 2);
    R3.addRoute("192.168.1.2", "192.168.1.2", 1);

    // Display initial routing tables
    cout << "\nInitial Routing Tables:\n";
    R1.displayRoutingTable();
    R2.displayRoutingTable();
    R3.displayRoutingTable();

    // Simulate dynamic routing updates
    cout << "\nSimulating dynamic routing updates...\n";
    
    // Simulate link failure between R1 and R2
    cout << "\nLink between R1 and R2 fails!\n";
    R1.removeRoute("192.168.1.2");
    R2.removeRoute("192.168.1.1");

    // Update routes through R3
    R1.addRoute("192.168.1.2", "192.168.1.3", 2);
    R2.addRoute("192.168.1.1", "192.168.1.3", 2);

    cout << "\nUpdated Routing Tables after link failure:\n";
    R1.displayRoutingTable();
    R2.displayRoutingTable();
    R3.displayRoutingTable();

    // Simulate packet transmission
    string sourceIP, destIP, data, protocol;
    cout << "\nEnter source IP: ";
    cin >> sourceIP;
    cout << "Enter destination IP: ";
    cin >> destIP;
    cout << "Enter data to send: ";
    cin.ignore();
    getline(cin, data);
    cout << "Choose protocol (Stop-and-Wait/Selective-Repeat): ";
    getline(cin, protocol);

    R1.sendPacket(sourceIP, destIP, data, protocol);
}
