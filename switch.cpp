#include "switch.h"
//#include "hub.h"
#include <thread>
#include <chrono>
std::vector<Switch> deviceListSwitch;

int Switch::calculateChecksum(const std::string& frame) {
    int checksum = 0;
    for (char c : frame) {
        checksum += c;
    }
    return checksum % 256;
}
void Switch::learnMacAddress(const std::string& mac_source, int port) {
    if (macTable.size() >= MAX_PORTS) {
        std::cout << "Error: Maximum port limit reached. Cannot add more devices." << std::endl;
        return;
    }
    macTable[mac_source] = port;
    connectedDevices.push_back(mac_source);
}

void Switch::forwardPacket(const std::string& mac_dest, int incomingPort) {
    if (macTable.find(mac_dest) != macTable.end()) {
        std::cout << "Packet forwarded to port " << macTable[mac_dest] << " for MAC: " << mac_dest << std::endl;
    } else {
        std::cout << "Flooding packet to all ports except " << incomingPort << " for MAC: " << mac_dest << std::endl;
    }
}

void Switch::applyAccessControl(const std::string& protocol, const std::string& senderMAC, const std::string& receiverMAC, const std::string& data) {
    if (protocol == "Stop-and-Wait") {
        stopAndWait(senderMAC, receiverMAC, data);
    } else if (protocol == "Selective-Repeat") {
        selectiveRepeat(senderMAC, receiverMAC, data);
    } else {
        std::cout << "Unknown protocol. Using default forwarding." << std::endl;
        forwardPacket(receiverMAC, macTable[senderMAC]);
    }
}


void Switch::stopAndWait(const std::string& senderMAC, const std::string& receiverMAC, const std::string& data) {
    std::srand(std::time(nullptr)); // Seed for randomization
    std::cout << "[Stop-and-Wait] Sending data from " << senderMAC << " to " << receiverMAC << "..." << std::endl;

    for (char c : data) {
        std::string frame(1, c);
        int checksum = calculateChecksum(frame);
        std::cout << "Sending frame: " << c << " with checksum: " << checksum << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate delay

        bool frameCorrupt = (std::rand() % 2 == 0);
        if (frameCorrupt) {
            std::cout << "Frame " << c << " corrupted! Requesting retransmission..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Resending frame: " << c << " with checksum: " << checksum << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "ACK received for frame: " << c << std::endl;
    }
    std::cout << "[Stop-and-Wait] Transmission successful." << std::endl;
}
//im not converting frames into data cause no data is actually transmitted 

void Switch::selectiveRepeat(const std::string& senderMAC, const std::string& receiverMAC, const std::string& data) {
    std::srand(std::time(nullptr)); // Seed for randomization
    std::cout << "[Selective Repeat] Sending frames from " << senderMAC << " to " << receiverMAC << "..." << std::endl;
    
    int base = 0;
    std::vector<bool> ackReceived(data.size(), false);
    while (base < data.size()) {
        for (int j = 0; j < WINDOW_SIZE; ++j) {
            int seqNum = (base + j) % SEQ_NUM_SIZE;
            if (base + j < data.size() && !ackReceived[base + j]) {
                std::string frame(1, data[base + j]);
                int checksum = calculateChecksum(frame);
                std::cout << "Sending frame " << seqNum << ": " << data[base + j] << " with checksum: " << checksum << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        for (int j = 0; j < WINDOW_SIZE; ++j) {
            int seqNum = (base + j) % SEQ_NUM_SIZE;
            if (base + j < data.size() && !ackReceived[base + j]) {
                bool frameLost = (std::rand() % 4 == 0);
                bool frameCorrupt = (std::rand() % 5 == 0);
                if (frameLost || frameCorrupt) {
                    std::cout << "Frame " << seqNum << " lost or corrupted! Requesting retransmission..." << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                } else {
                    std::cout << "Frame " << seqNum << " successfully received." << std::endl;
                    ackReceived[base + j] = true;
                }
            }
        }
        
        while (base < data.size() && ackReceived[base % SEQ_NUM_SIZE]) {
            ++base;
        }
    }
    std::cout << "[Selective Repeat] All frames acknowledged. Transmission successful." << std::endl;
}//this function is half done using internet



void Switch::displayConnectedDevices() {
    std::cout << "Connected Devices and Ports:" << std::endl;
    for (const auto& entry : macTable) {
        std::cout << "MAC Address: " << entry.first << " -> Port: " << entry.second << std::endl;
    }
}
void Switch::connectDevice(const std::string& macAddress) {
    if (macTable.size() >= MAX_PORTS) {
        std::cout << "Error: Maximum port limit reached. Cannot add more devices." << std::endl;
        return;
    }
    int port = (macTable.size() % MAX_PORTS) + 1; // Assign port using modulo operation
    learnMacAddress(macAddress, port);
    std::cout << "Device with MAC " << macAddress << " connected at port " << port << std::endl;
}
void Switch::refreshMacTable() {
    std::cout << "Refreshing MAC Table..." << std::endl;
    macTable.clear();  // Clear existing entries
   
    std::cout << "MAC Table refreshed." << std::endl;
}
// void Switch:: connectHub(Hub* hub) {
//     connectedHubs.push_back(hub);
//     hub->connectToSwitch(this); // Create bidirectional connection
// }
void initilizeSwitches() {
    Switch switch1, switch2;
    switch1.setDevice("00:3A:4B:5C:6D:7E");
    switch2.setDevice("00:3B:4C:5D:6E:7F");
    deviceListSwitch.push_back(switch1); 
    deviceListSwitch.push_back(switch2);
    
}
void Switch::setDevice(const std::string& mac_address) {
    this->mac_address = mac_address;
    
}
std::string Switch::getMacAddress() const {
    return mac_address;
}

// void connectHub(Hub* hub) {
//     connectedHubs.push_back(hub);
//     cout << "Hub connected to switch." << endl;
// }
void Switch::connectHub(Hub* hub) {
    if (connectedHubs.size() >= MAX_PORTS) {
        std::cout << "Error: Maximum port limit reached. Cannot connect more hubs." << std::endl;
        return;
    }
    connectedHubs.push_back(hub);
    hub->connectToSwitch(this); // Establish bidirectional connection
    std::cout << "Hub connected to switch successfully." << std::endl;
}