#include "device.h"
#include <vector>

std::vector<Devices> deviceList;

void Devices::setDevice(const string& mac_address, const string& ip_address) {
    this->mac_address = mac_address;
    this->ip_address = ip_address;
}

string Devices::getMacAddress() const {
    return mac_address;
}

string Devices::getIpAddress() const {
    return ip_address;
}


void initializeDevices() {
    Devices pc1, pc2, pc3;
    pc1.setDevice("00:1A:2B:3C:4D:5E", "192.168.1.2");
    pc2.setDevice("00:1B:3C:4D:5E:6F", "192.168.1.3");
    pc3.setDevice("00:1C:2D:3E:4F:5G", "192.168.1.4");
    
    deviceList.push_back(pc1);//this will be at index 0
    deviceList.push_back(pc2);
    deviceList.push_back(pc3);
}

