#include "switch.h"
std::vector<Switch> deviceListswitch;

void Switch::setSwitch(const string& mac_address) {
    this->mac_address = mac_address;
    //int portcouter;keep track of avilable ports
}
std::string Switch::getSwitch_mac() const {
    return mac_address;
}
void Switch::connectDevice(Devices* device) {
    connectedDevices.push_back(device);
    cout << "Device with MAC: " << device->getMacAddress() << " connected to switch." << endl;
}

void Switch::forwardData(const string& senderMAC, const string& receiverMAC, const string& data) {
    //  Step 1: Learn the Sender's MAC Address
    if (macTable.find(senderMAC) == macTable.end()) {
        for (auto& device : connectedDevices) {
            if (device->getMacAddress() == senderMAC) {
                macTable[senderMAC] = device;
                cout << "MAC Learning: Stored " << senderMAC << " in MAC table." << endl;
                break;
            }
        }
    }

    cout << "\nSwitch processing data from " << senderMAC << " to " << receiverMAC << endl;

    // Check if the Destination MAC is Known
    if (macTable.find(receiverMAC) != macTable.end()) {
        cout << " -> Directly forwarding to device with MAC: " << receiverMAC << endl;
    } else {
        // Broadcast Since Destination MAC is Unknown
        cout << " -> Destination port unknown, broadcasting..." << endl;
        for (auto& device : connectedDevices) {
            if (device->getMacAddress() != senderMAC) {
                cout << " -> Sent to device with MAC: " << device->getMacAddress() << endl;
            }
        }
    }

    //   Learn the Receiver’s MAC Address When It Responds
    for (auto& device : connectedDevices) {
        if (device->getMacAddress() == receiverMAC && macTable.find(receiverMAC) == macTable.end()) {
            macTable[receiverMAC] = device;
            cout << "MAC Learning: Stored " << receiverMAC << " in MAC table." << endl;
            break;
        }
    }
}

// Display all MAC table entries
void Switch::displayMacTable() const {
    cout << "\nMAC Table:\n";
    if (macTable.empty()) {
        cout << " - MAC table is empty.\n";
        return;
    }
    for (const auto& entry : macTable) {
        cout << " - MAC: " << entry.first << " -> Device\n";
    }
}

// Display all connected devices
void Switch::displayConnectedDevices() const {
    cout << "\nConnected Devices:\n";
    if (connectedDevices.empty()) {
        cout << " - No devices connected.\n";
        return;
    }
    for (const auto& device : connectedDevices) {
        cout << " - MAC: " << device->getMacAddress() 
             << " | IP: " << device->getIpAddress() << endl;
    }
}
void initializeSwitches(vector<Switch>& deviceListSwitch, const string& mac_address1, const string& mac_address2) {
    Switch switch1;
    switch1.setSwitch("00:1E:67:A3:BC:9F");
    deviceListSwitch.push_back(switch1);

    Switch switch2;
    switch2.setSwitch("00:2A:5B:8C:7D:3E");
    deviceListSwitch.push_back(switch2);

    
}
//i have assumed mac table entry is port number 