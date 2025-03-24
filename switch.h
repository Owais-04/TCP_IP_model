#ifndef SWITCH_H
#define SWITCH_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include "hub.h"


class Switch {
private:
    std::string mac_address;
    std::unordered_map<std::string, int> macTable; // Maps MAC address to port number
    std::vector<std::string> connectedDevices; // Stores MAC addresses of connected devices
    // Define a maximum number of ports
    
public:
    
    static const int MAX_PORTS = 10; 
    static const int WINDOW_SIZE = 3; 
    static const int SEQ_NUM_SIZE = 8;
   
    int calculateChecksum(const std::string& frame);
    void forwardPacket(const std::string& mac_dest, int incomingPort);
    void learnMacAddress(const std::string& mac_source, int port);
    void applyAccessControl(const std::string& protocol, const std::string& senderMAC, const std::string& receiverMAC, const std::string& data);
    void stopAndWait(const std::string& senderMAC, const std::string& receiverMAC, const std::string& data);
    void selectiveRepeat(const std::string& senderMAC, const std::string& receiverMAC, const std::string& data);
    void displayConnectedDevices(); // connected devices and ports
    void connectDevice(const std::string& macAddress); // Adds device to the switch
    void refreshMacTable();
    //void connectHub(Hub* hub);
    void setDevice(const std::string & mac_address);
    std:: string getMacAddress() const;
    //std:: vector<Hub*> connectedHubs;
};

void initilizeSwitches();
#endif