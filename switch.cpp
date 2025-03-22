#include "switch.h"

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

    //  Step 2: Check if the Destination MAC is Known
    if (macTable.find(receiverMAC) != macTable.end()) {
        cout << " -> Directly forwarding to device with MAC: " << receiverMAC << endl;
    } else {
        // Step 3: Broadcast Since Destination MAC is Unknown
        cout << " -> Destination MAC unknown, broadcasting..." << endl;
        for (auto& device : connectedDevices) {
            if (device->getMacAddress() != senderMAC) {
                cout << " -> Sent to device with MAC: " << device->getMacAddress() << endl;
            }
        }
    }

    //  Step 4: Learn the Receiver’s MAC Address When It Responds
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
