#include <iostream>
#include <vector>
#include "device.h"
using namespace std;

int main() {
    vector<Devices> deviceList; 

    
    Devices device1, device2, device3;
    
    device1.setDevice("00:1A:2B:3C:4D:5E", "192.168.1.2");
    device2.setDevice("00:1B:3C:4D:5E:6F", "192.168.1.3");
    device3.setDevice("00:1C:2D:3E:4F:5G", "192.168.1.4");

    deviceList.push_back(device1);
    deviceList.push_back(device2);
    deviceList.push_back(device3);

    // Display device information
    for (int i = 0; i < deviceList.size(); i++) {
        cout << "Device " << i + 1 << " - MAC: " 
             << deviceList[i].getMacAddress() 
             << ", IP: " << deviceList[i].getIpAddress() << endl;
    }

    return 0;
}
