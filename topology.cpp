#include "topology.h"
#include "device.h"
#include "hub.h"
#include "bus.h"
#include "switch.h"
#include <iostream>
#include "paramhs.h"
#include "bridge.h"

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
    int device,device2;
    string message;
    Hub hub;
    for (auto& device : deviceList) {
        hub.connectDevice(&device);
    }
    cout<<"what is the sender device :(devices start from 0-2)"<<endl;
    cin>>device;
    cout<<"enter the message you want to send :"<<endl;
    cin>>message;
    cout<<"enter the receving device :"<<endl;
    cin>>device2;
    hub.broadcastData(deviceList[device].getMacAddress(), message);
    hub.displayConnectedDevices();
    hub.broadcastData(deviceList[device2].getMacAddress(), "ACK from " + deviceList[device2].getMacAddress());
   
}
void starTopology_switch() {
    int device, device2;
    string message;
    Switch networkSwitch;
    for (auto& device : deviceList) {
        networkSwitch.connectDevice(&device);
    }
    // Forward data from one device to another
    //add dynamic addition of sender and receiver
    cout<<"what is the sending device?(0-2)"<<endl;
    cin>>device;
    cout<<"what is the receving device?(other than sending)"<<endl;
    cin>>device2;
    cout<<"enter the message?"<<endl;
    cin>>message;
    networkSwitch.forwardData(deviceList[device].getMacAddress(),  deviceList[device2].getMacAddress(),message);
    
    networkSwitch.displayConnectedDevices();
}
//  void hardwired_layer2(){
       
// //     Bridge networkbridge; 
// //     networkswitch.connectDevice(&deviceList[0]);
// //     networkswitch2.connectDevice(&deviceList[1]);
// //     networkswitch2.connectDevice(&deviceList[2]);
// //     networkswitch.connectDevice(&deviceList[3]);
// //     networkbridge.forwardFrame()

void busTopology() {
   int device,device2;
   string message;
    Bus bus;
    for (auto& device : deviceList) {
        bus.connectDevice_bus(&device);
    }
    cout<<"what is the sending device?(0-2)"<<endl;
    cin>>device;
    cout<<"enter receving device?(0-2) other than sending device"<<endl;
    cin>>device2;
    cout<<"enter the message!"<<endl;
    cin>>message;
    bus.transmitData_bus(deviceList[device].getMacAddress(), message, deviceList[device2].getMacAddress());
    //bus.transmitData_bus(deviceList[device2].getMacAddress(),"Ack from "+deviceList[device2].getMacAddress(), deviceList[device].getMacAddress() );
    bus.displayConnectedDevices_bus();
}


//  void ringTopology(){
// //     Ring ring;
// //     ring.connectDevices_ring(&device);

//  }