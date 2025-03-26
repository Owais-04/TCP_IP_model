#include <iostream>
#include "paramhs.h"
#include "bus.h"


void Bus::connectDevice_bus(EndDevices* device) {
    connectedDevices.push_back(device);
    std::cout << "Device with MAC: " << device->getMacAddress() << " connected with bus " << std::endl;
}
void Bus::transmitData_bus(const string& senderMAC, const string& data,const string& receiverMac) {
    cout << "\nBroadcasting data from " << senderMAC << " to all devices, data= " << data << endl;
    
    for (auto& device : connectedDevices) {
        if (device->getMacAddress() != senderMAC) {
            cout << " -> Sent to device with MAC: " << device->getMacAddress() << endl;
        }
    }
    // for(auto & device : connectedSwitches){
    //    cout<<" -> sent to switch with Mac " <<device->getMacAddress()<<endl;
    // }
}


void Bus::displayConnectedDevices_bus() const {
    std::cout << "\nConnected Devices:" << std::endl;
    for (auto& device : connectedDevices) {
        cout << " - MAC: " << device->getMacAddress() 
             << " | IP: " << device->getIpAddress() << endl;
    }
}
void Bus::TransmitAck(const string& senderMAC) {
    cout << "\nBroadcasting ack from " << senderMAC  << endl;
    
    for (auto& device : connectedDevices) {
        if (device->getMacAddress() != senderMAC) {
            cout << " -> Sent to device with MAC: " << device->getMacAddress() << endl;
        }
    }
    // for(auto&device :connectedSwitches ){
    //     cout<<" -> sent to switch with Mac "<<device->getMacAddress()<<endl;
    // }
}