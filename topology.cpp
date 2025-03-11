#include "topology.h"
#include "device.h"
#include "hub.h"
#include "bus.h"
#include <iostream>
#include "paramhs.h"

using namespace std;
void choose_Topology(int x) {
    switch(x) {
        case 1:
            starTopology();
            break;
        case 2:
            busTopology();
            break;
        case 3:
            ringTopology();
            break;
        default:
            std::cout << "Invalid topology choice" << std::endl;
            break;
    }
}
void starTopology() {
    Hub hub;
    for (auto& device : deviceList) {
        hub.connectDevice(&device);
    }
    hub.broadcastData(deviceList[0].getMacAddress(), "Hello from device 1");
    hub.displayConnectedDevices();
}

void busTopology() {
   Bus bus;
   for (auto& device : deviceList) {
    bus.connectDevice_bus(&device);
}
bus.transmitData_bus(deviceList[0].getMacAddress(),"hello from device 1",deviceList[2].getMacAddress());
bus.displayConnectedDevices_bus();
}
void ringTopology(){
}