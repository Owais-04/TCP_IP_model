#include "hub.h"
#include <iostream>

void Hub::connectDevice(EndDevices* device) {
    connectedDevices.push_back(device);
    cout << "Device with MAC: " << device->getMacAddress() << " connected to hub." << endl;
}

void Hub::broadcastData(const string& senderMAC, const string& data) {
    cout << "\nBroadcasting data from " << senderMAC << "00:1A:2B:3C:4D:5E " << data << endl;
    
    for (auto& device : connectedDevices) {
        if (device->getMacAddress() != senderMAC) {
            cout << " -> Sent to device with MAC: " << device->getMacAddress() << endl;
        }
    }
}

void Hub::displayConnectedDevices() const {
    cout << "\nConnected Devices:" << endl;
    for (auto& device : connectedDevices) {
        cout << " - MAC: " << device->getMacAddress() 
             << " | IP: " << device->getIpAddress() << endl;
    }
}
