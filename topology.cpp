#include "topology.h"
#include "device.h"
#include "hub.h"
#include "bus.h"
#include "switch.h"
#include <iostream>
#include "paramhs.h"
#include "bridge.h"
#include <thread>
#include <chrono>

using namespace std;
void choose_Topology_layer2(int x){
    switch(x){
        case 1:
       // cout<<"star using switch :"<<endl;
       starTopology_switch();
       break;
    //    case 2://hard wired connection to show working of intermixed ckt
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
    std::string message, protocol;
    Switch networkSwitch;
    initializeEndDevices(); // Ensure devices are initialized

    // Connect devices and assign ports
    int port = 1;
    for (auto& dev : deviceList) {
        if (port > Switch::MAX_PORTS) {
            std::cout << "Max ports reached. Cannot connect more devices." << std::endl;
            break;
        }
        networkSwitch.learnMacAddress(dev.getMacAddress(), port++);
    }

    std::cout << "What is the sending device? (0-" << deviceList.size() - 1 << ")" << std::endl;
    std::cin >> device;
    std::cout << "What is the receiving device? (other than sending)" << std::endl;
    std::cin >> device2;
    std::cout << "Enter the message:" << std::endl;
    std::cin >> message;
    std::cout << "Choose protocol (Stop-and-Wait / Selective Repeat):" << std::endl;
    std::cin >> protocol;

    // Apply access control and forward packets accordingly
    networkSwitch.applyAccessControl(protocol, deviceList[device].getMacAddress(), deviceList[device2].getMacAddress(), message);
    
    // Display MAC table and connected devices
    networkSwitch.displayConnectedDevices();
    // Simulate periodic refresh (add this after sending data)
   std::this_thread::sleep_for(std::chrono::seconds(5)); // Wait 5 seconds before refreshing
      networkSwitch.refreshMacTable();
     networkSwitch.displayConnectedDevices();

}

//  void hardwired_layer2(){
//     int switch1mac,switch2mac;
//     initializeSwitches();
//     // Bridge bridge;
//     // int device1,device2;
//     // cout<<"i have created a hardwired topology!"<<endl;
//     // Switch switch1;
//     // Switch switch2;
//     // bridge.learnMacAddress(&switch1mac,0);
//     // bridge.learnMacAddress(&switch2mac,1);

//  }
       

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