#include "topology.h"
#include "device.h"
#include "hub.h"
#include "bus.h"
#include "switch.h"
#include <iostream>
#include "paramhs.h"

using namespace std;
void choose_Topology_layer2(int x){
    switch(x){
        case 1:
       // cout<<"star using switch :"<<endl;
       starTopology_switch();
       break;
    //    case 2://hard wired connection to show working of intermixed circut
    //    hardwired_layer2();
    //    break;
     case 3:
     cout<<"invalid "<<endl;

    }
}
void choose_Topology(int x) {
    switch(x) {
        case 1:
            starTopology();
            break;
        case 2:
            busTopology();
            break;
        // case 3:
        //     ringTopology();
        //     break;
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
void starTopology_switch() {
    Switch networkSwitch;
    for (auto& device : deviceList) {
        networkSwitch.connectDevice(&device);
    }
    // Forward data from one device to another
    //add dynamic addition of sender and receiver
    networkSwitch.forwardData(deviceList[0].getMacAddress(),  deviceList[1].getMacAddress(),"Hello from device 1");
    
    networkSwitch.displayConnectedDevices();
}
// void hardwired_layer2(){
//     cout<<"what type of intermediate device you want to add and how many :"<<endl;
//     int choice;
 
//     cout<<"1. for bridge \n2. for switch \n3. for hub"
// }

void busTopology() {
   Bus bus;
   for (auto& device : deviceList) {
    bus.connectDevice_bus(&device);
}
bus.transmitData_bus(deviceList[0].getMacAddress(),"hello from device 1",deviceList[2].getMacAddress());
bus.displayConnectedDevices_bus();
}
 void ringTopology(){
//     Ring ring;
//     ring.connectDevices_ring(&device);

 }