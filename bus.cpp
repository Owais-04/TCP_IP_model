#include <iostream>
#include "paramhs.h"
#include "bus.h"


void Bus::connectDevice_bus(Devices* device) {
    connectedDevices.push_back(device);
    std::cout << "Device with MAC: " << device->getMacAddress() << " connected with bus " << std::endl;
}
void Bus::transmitData_bus(const std::string& senderMAC, const std::string& data, const std::string& receiverMAC) {
    std::cout << "\nTransmitting data from " << senderMAC << " to " << receiverMAC << "  " << data << std::endl;
    
    
    for (auto& device : connectedDevices) {
        if (device->getMacAddress() != senderMAC && device->getMacAddress() == receiverMAC) {
            std::cout << " -> message received device with MAC: " << device->getMacAddress() << std::endl;
        }
    }
}
void Bus::displayConnectedDevices_bus() const {
    std::cout << "\nConnected Devices:" << std::endl;
    for (auto& device : connectedDevices) {
        cout << " - MAC: " << device->getMacAddress() 
             << " | IP: " << device->getIpAddress() << endl;
    }
}