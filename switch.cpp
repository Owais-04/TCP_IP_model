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
    return checksum % 256;//so that it fits in 8 bits
}
// bool Switch::verifyChecksum(const std::string& frame, int receivedChecksum) {
//     int calculatedChecksum = calculateChecksum(frame);
//     if (calculatedChecksum == receivedChecksum) {
//         std::cout << "Checksum verification passed for frame: " << frame << std::endl;
//         return true;
//     } else {
//         std::cout << "Checksum verification failed for frame: " << frame 
//                   << ". Expected: " << calculatedChecksum 
//                   << ", Received: " << receivedChecksum << std::endl;
//         return false;
//     }
// }
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
//flow control
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
    std::cout << " Sending data from " << senderMAC << " to " << receiverMAC << "..." << std::endl;

    for (char c : data) {
        std::string frame(1, c);
        int checksum = calculateChecksum(frame);

        bool ackReceived = false;
        int attempts = 0;

        while (!ackReceived && attempts < 3) { // Retransmit up to 3 times
            std::cout << "Sending frame: " << c << " with checksum: " << checksum << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            bool introduceError = (std::rand() % 4 == 0);
            int receivedChecksum = introduceError ? checksum + 1 : checksum;

            // Simulate lost ACK
            bool ackLost = (std::rand() % 5 == 0);

            if (calculateChecksum(frame) != receivedChecksum) {
                std::cout << "Error detected in frame: " << c << "! Checksum received :" <<receivedChecksum<< std::endl;
                std::cout << "Requesting retransmission..." << std::endl;
            } else if (ackLost) {
                std::cout << "ACK lost! Retransmitting frame..." << std::endl;
            } else {
                std::cout << "ACK received for frame: " << c << std::endl;
                ackReceived = true;
            }
            attempts++;
        }

        if (!ackReceived) {
            std::cout << "Transmission failed after multiple attempts for frame: " << c << std::endl;
            return;
        }
    }
    std::cout << " Transmission successful." << std::endl;
}



//im not converting frames into data because no data is actually transmitted 
//multiple frames sent before ack is received
void Switch::selectiveRepeat(const std::string& senderMAC, const std::string& receiverMAC, const std::string& data) {
    std::srand(std::time(nullptr)); // Seed for randomization
    std::cout << "Sending frames from " << senderMAC << " to " << receiverMAC << "..." << std::endl;

    int base = 0;
    std::vector<bool> ackReceived(data.size(), false);

    while (base < data.size()) {
        for (int j = 0; j < WINDOW_SIZE; ++j) {
            int seqNum = (base + j) % SEQ_NUM_SIZE;
            if (base + j < data.size() && !ackReceived[base + j]) {
                std::string frame(1, data[base + j]);
                int checksum = calculateChecksum(frame);

                bool introduceError = (std::rand() % 5 == 0);
                int receivedChecksum = introduceError ? checksum + 1 : checksum;

                std::cout << "Sending frame " << seqNum << ": " << data[base + j] << " with checksum: " << checksum << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));

                bool ackLost = (std::rand() % 5 == 0);
                if (calculateChecksum(frame) != receivedChecksum) {
                    std::cout << "Frame " << seqNum << " corrupted! Requesting retransmission..." << std::endl;
                } else if (ackLost) {
                    std::cout << "ACK lost for frame " << seqNum << "! Retransmitting..." << std::endl;
                } else {
                    std::cout << "ACK received for frame " << seqNum << std::endl;
                    ackReceived[base + j] = true;
                }
            }
        }

        // forwarding base index
        while (base < data.size() && ackReceived[base]) {
            ++base;
        }
    }
    std::cout << " All frames acknowledged. Transmission successful." << std::endl;
}






void Switch::displayConnectedDevices() {
    cout << "Switch Connection Details:" << endl;
    
    
    cout << "Switch MAC Address: " << mac_address << endl;
    

    cout << "\nConnected Hubs:" << endl;
    if (connectedHubs.empty()) {
        cout << "No hubs connected to the switch" << endl;
    } else {
        for (size_t i = 0; i < connectedHubs.size(); i++) {
            cout << "Hub " << i+1 << " connected to Switch on port " << i+1 << endl;
        }
    }
    
    
    cout << "\nDirectly Connected End Devices:" << endl;
    if (connectedDevices.empty()) {
        cout << "No devices directly connected to the switch" << endl;
    } else {
        for (const auto& deviceMac : connectedDevices) {
        
            int port = -1;
            for (const auto& entry : macTable) {
                if (entry.first == deviceMac) {
                    port = entry.second;
                    break;
                }
            }
            
            cout << "Device MAC: " << deviceMac 
                 << " (Port: " << port << ")" << endl;
        }
    }
    
  
}
void Switch::connectDevice(const std::string& macAddress) {
    // if (macTable.size() >= MAX_PORTS) {
    //     std::cout << "Error: Maximum port limit reached. Cannot add more devices." << std::endl;
    //     return;
    // }
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
    int port = (connectedHubs.size() % MAX_PORTS) + 1; // Assign port using modulo operation
    connectedHubs.push_back(hub);
    hub->connectToSwitch(this); // Establish bidirectional connection
    std::cout << "Hub connected to switch on port " << port << std::endl;
}
bool Switch::isDeviceDirectlyConnected(const string& macAddress) {
    // Check if the device is directly connected to the switch
    for (const auto& device : connectedDevices) {
        if (device == macAddress) {
            return true;
        }
    }
    return false;
}