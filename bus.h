#ifndef BUS_H
#define BUS_H

#include "device.h"  
#include <vector>
#include <string>
using namespace std;

class Bus {
private:
    vector<EndDevices*> connectedDevices;  

public:
    
    void connectDevice_bus(EndDevices* device);

    
    void transmitData_bus(const string& senderMAC, const string& data,const string& receiverMAC);

    void displayConnectedDevices_bus() const;
    void TransmitAck(const string& senderMAC);
};

#endif