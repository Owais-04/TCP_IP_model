#ifndef HUB_H
#define HUB_H

#include "device.h"  
#include "switch.h"
#include <vector>
#include <string>

class Switch; // Forward declaration
using namespace std;

class Hub {
private:
    vector<EndDevices*> connectedDevices;  
    vector<Switch*> connectedSwitches;
public:
    
    void connectDevice(EndDevices* device);

    
    void broadcastData(const string& senderMAC, const string& data);

    
    void displayConnectedDevices() const;
    void broadcastAck(const string& senderMAC);
    
    void connectToSwitch(Switch* switchDevice);
};

#endif
