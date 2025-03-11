#ifndef BUS_H
#define BUS_H

#include "device.h"  
#include <vector>
#include <string>
using namespace std;

class Bus {
private:
    vector<Devices*> connectedDevices;  

public:
    
    void connectDevice_bus(Devices* device);

    
    void transmitData_bus(const string& senderMAC, const string& data,const string& receiverMAC);

    void displayConnectedDevices_bus() const;
   
};

#endif