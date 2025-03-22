#ifndef HUB_H
#define HUB_H

#include "device.h"  
#include <vector>
#include <string>
using namespace std;

class Hub {
private:
    vector<Devices*> connectedDevices;  

public:
    
    void connectDevice(Devices* device);

    
    void broadcastData(const string& senderMAC, const string& data);
//broad cast ack
    
    void displayConnectedDevices() const;
};

#endif
