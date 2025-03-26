#include "hub.h"
#include "device.h"
#include <iostream>

void Hub::connectDevice(EndDevices* device) {
    connectedDevices.push_back(device);
    cout << "Device with MAC: " << device->getMacAddress() << " connected to hub." << endl;
}

void Hub::broadcastData(const string& senderMAC, const string& data) {
    cout << "\nBroadcasting data from " << senderMAC << " to all devices, data= " << data << endl;
    
    for (auto& device : connectedDevices) {
        if (device->getMacAddress() != senderMAC) {
            cout << " -> Sent to device with MAC: " << device->getMacAddress() << endl;
        }
    }
    for(auto & device : connectedSwitches){
       cout<<" -> sent to switch with Mac " <<device->getMacAddress()<<endl;
    }
}


void Hub:: connectToSwitch(Switch* switchDevice) {
    connectedSwitches.push_back(switchDevice);
    cout<<"switch with mac: "<<switchDevice->getMacAddress()<<" connected to hub"<<endl;
}
void Hub::displayConnectedDevices() const {
    cout << "\nConnected Devices:" << endl;
    for (auto& device : connectedDevices) {
        cout << " - MAC: " << device->getMacAddress() 
             << " | IP: " << device->getIpAddress() << endl;
    }
    for(auto& device: connectedSwitches){//changed here
        cout << " - MAC: " << device->getMacAddress()<<endl;
    }
}

void Hub::broadcastAck(const string& senderMAC) {
    cout << "\nBroadcasting ack from " << senderMAC  << endl;
    
    for (auto& device : connectedDevices) {
        if (device->getMacAddress() != senderMAC) {
            cout << " -> Sent to device with MAC: " << device->getMacAddress() << endl;
        }
    }
    for(auto&device :connectedSwitches ){
        cout<<" -> sent to switch with Mac "<<device->getMacAddress()<<endl;
    }
}
bool Hub::isDeviceConnected(const string& macAddress) {
    // Check if the device is connected to this hub
    for (auto& device : connectedDevices) {
        if (device->getMacAddress() == macAddress) {
            return true;
        }
    }
    return false;
}