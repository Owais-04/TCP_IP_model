#ifndef SWITCH_H
#define SWITCH_H

#include "device.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Switch{
private:
    string mac_address;
    vector<Devices*> connectedDevices;
    unordered_map<string, Devices*> macTable; // MAC address -> Device pointer

public:
    void setSwitch(const string& mac_address);
    string getSwitch_mac() const;
    void connectDevice(Devices* device);

    void forwardData(const string& senderMAC, const string& receiverMAC, const string& data);
    void displayMacTable() const;
    void displayConnectedDevices() const;
};
void initializeSwitches(vector<Switch>& deviceListSwitch, const string& mac_address);


#endif
