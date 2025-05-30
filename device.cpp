#include "device.h"
#include <vector>
#include <iostream>
std::vector<EndDevices> deviceList;

void EndDevices::setDevice(const string& mac_address, const string& ip_address) {
    this->mac_address = mac_address;
    this->ip_address = ip_address;
}

string EndDevices::getMacAddress() const {
    return mac_address;
}

string EndDevices::getIpAddress() const {
    return ip_address;
}


void initializeEndDevices() {
    EndDevices pc1, pc2, pc3, pc4, pc5, pc6, pc7, pc8, pc9, pc10;
    pc1.setDevice("00:1A:2B:3C:4D:5E", "192.168.1.2");
    pc2.setDevice("00:1B:3C:4D:5E:6F", "192.168.1.3");
    pc3.setDevice("00:1C:2D:3E:4F:5G", "192.168.1.4");
    pc4.setDevice("00:1D:2E:3F:4G:5H", "192.168.1.5");
    pc5.setDevice("00:1E:2F:3G:4H:5I", "192.168.1.6");
    pc6.setDevice("00:1F:2G:3H:4I:5J", "192.168.1.7");
    pc7.setDevice("00:2A:3B:4C:5D:6E", "192.168.1.8");
    pc8.setDevice("00:2B:3C:4D:5E:6F", "192.168.1.9");
    pc9.setDevice("00:2C:3D:4E:5F:6G", "192.168.1.10");
    pc10.setDevice("00:2D:3E:4F:5G:6H", "192.168.1.11");
    int n;
    cout<<"enter the number of devices you want to use: "<<endl;
    cin>>n;
    for (int i = 0; i < n; i++) {
        switch (i) {
            case 0: deviceList.push_back(pc1); break;
            case 1: deviceList.push_back(pc2); break;
            case 2: deviceList.push_back(pc3); break;
            case 3: deviceList.push_back(pc4); break;
            case 4: deviceList.push_back(pc5); break;
            case 5: deviceList.push_back(pc6); break;
            case 6: deviceList.push_back(pc7); break;
            case 7: deviceList.push_back(pc8); break;
            case 8: deviceList.push_back(pc9); break;
            case 9: deviceList.push_back(pc10); break;
            default: 
                std::cout << "Only 10 devices are available. Ignoring extra devices." << std::endl;
                return;
        }
    }
    
}

