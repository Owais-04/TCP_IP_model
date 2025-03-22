#ifndef SWITCH_H
#define SWITCH_H

#include "device.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Switch {
private:
    vector<Devices*> connectedDevices;
    unordered_map<string, Devices*> macTable; // MAC address -> Device pointer

public:
    void connectDevice(Devices* device);
    void forwardData(const string& senderMAC, const string& receiverMAC, const string& data);
    void displayMacTable() const;
    void displayConnectedDevices() const;
};

#endif
