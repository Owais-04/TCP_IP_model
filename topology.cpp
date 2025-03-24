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
     default:
     cout<<"invalid "<<endl;
      break;
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
            cout << "Invalid topology choice" << endl;
            break;
    }
}
void testcases_layer1(){
    int choice;
    cout<<"1 for first test case \n2 for second test case :"<<endl;
    cin>>choice;
    switch (choice){
        case 1:
        testcase1_layer1();
        break;
        case 2:
        testcase2_layer1();
        break;
        case 3:
        cout<<"invalid"<<endl;
    }
}
void testcases_layer2(){
    int choice;
    cout<<"1 for first test case \n2 for second test case :"<<endl;
    cin>>choice;
    switch (choice){
        case 1:
        testcase1_layer2();
        break;
        case 2:
        testcase2_layer2();
        break;
        case 3:
        cout<<"invalid"<<endl;
}  
}
void testcase1_layer2(){
  starTopology_switch();
}  
//this test case is not that correct implementation as i have not used bridge properties correctly;
void testcase2_layer2() {
    // Create two hubs
    Hub h1, h2;
    Switch centralSwitch;
    centralSwitch.setDevice("A4:B1:C2:3D:E5:F6");
    
    cout << "\n===== Setting up network topology =====" << endl;
    cout << "Creating two star topologies with 5 devices each, connected via a switch" << endl;
    
    // Connect first 5 devices to h1
    cout << "\nConnecting devices 0-4 to Hub 1:" << endl;
    for (int i = 0; i < 5; i++) {
        h1.connectDevice(&deviceList[i]);
    }

    // Connect last 5 devices to h2
    cout << "\nConnecting devices 5-9 to Hub 2:" << endl;
    for (int i = 5; i < 10; i++) {
        h2.connectDevice(&deviceList[i]);
    }

    // Connect hubs to the central switch
    cout << "\nConnecting both hubs to the central switch" << endl;
    centralSwitch.connectHub(&h1);
    centralSwitch.connectHub(&h2);
    
    // Display connected devices
    cout << "\n===== Network Setup Complete =====" << endl;
    cout << "\nHub 1 connected devices:" << endl;
    h1.displayConnectedDevices();
    cout << "\nHub 2 connected devices:" << endl;
    h2.displayConnectedDevices();
    
    // Get sender and receiver
    cout << "\n===== Communication Setup =====" << endl;
    cout << "Select two PCs to enable communication:" << endl;
    cout << "Sender device (0-9): ";
    int senderIndex;
    cin >> senderIndex;

    cout << "Receiver device (0-9): ";
    int receiverIndex;
    cin >> receiverIndex;

    if (senderIndex < 0 || senderIndex >= 10 || receiverIndex < 0 || receiverIndex >= 10 || senderIndex == receiverIndex) {
        cout << "Invalid device indices!" << endl;
        return;
    }

    // Get message
    string message;
    cout << "Enter the message you want to send: ";
    cin.ignore();
    getline(cin, message);

    string senderMAC = deviceList[senderIndex].getMacAddress();
    string receiverMAC = deviceList[receiverIndex].getMacAddress();

    cout << "\n===== Starting Communication =====" << endl;
    cout << "Sending message from Device " << senderIndex 
         << " (MAC: " << senderMAC << ") to Device " << receiverIndex 
         << " (MAC: " << receiverMAC << ")" << endl;
    cout << "Message: \"" << message << "\"" << endl;
    
    // Learn MAC addresses at the switch
    int senderHubPort = (senderIndex < 5) ? 1 : 2;  // Port 1 for Hub1, Port 2 for Hub2
    int receiverHubPort = (receiverIndex < 5) ? 1 : 2;
    
    // The switch learns the sender's MAC address when it first sees traffic
    centralSwitch.learnMacAddress(senderMAC, senderHubPort);
    
    
    
    // Determine which hub the sender and receiver belong to
    if (senderIndex < 5) { 
    
        h1.broadcastData(senderMAC, message);
        
        if (receiverIndex < 5) { // Receiver is also in Hub 1
            
            h1.broadcastAck(receiverMAC);
        } else { // Receiver is in Hub 2
            
            
            // Switch forwards data to Hub 2 because receiver is there
            
            centralSwitch.forwardPacket(receiverMAC, senderHubPort);
            
            
            h2.broadcastAck(receiverMAC);
            
            // ACK travels back
        
            centralSwitch.forwardPacket(senderMAC, receiverHubPort);
            h1.broadcastAck(receiverMAC);
        
        }
    } else { // Sender is in Hub 2
        
        h2.broadcastData(senderMAC, message);
        
        if (receiverIndex >= 5) { // Receiver is also in Hub 2
          
            h2.broadcastAck(receiverMAC);
        } else { // Receiver is in Hub 1
            
            // Switch forwards data to Hub 1 because receiver is there
            h2.broadcastAck(receiverMAC);
            centralSwitch.forwardPacket(receiverMAC, senderHubPort);
            
           
            h1.broadcastAck(receiverMAC);
            
            // ACK travels back
           
            centralSwitch.forwardPacket(senderMAC, receiverHubPort);
            
            
        }
    }
    
 
}




void testcase2_layer1(){
    starTopology();
}
void testcase1_layer1(){
    initializeEndDevices();
    int device,device2;
    string message;
    cout<<"what is the sender device :(devices start from 0-2)"<<endl;
    cin>>device;
    cout<<"enter the message you want to send :"<<endl;
    cin>>message;
    cout<<"enter the receving device :"<<endl;
    cin>>device2;
    cout<<"device "<<deviceList[device].getMacAddress()<<" is sending message "<<message<<" to device "<<deviceList[device2].getMacAddress()<<endl;

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
    
    hub.broadcastAck(deviceList[device2].getMacAddress());
   
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
   
    std::cout << "What is the sending device? (1-9)"<< std::endl;
    std::cin >> device;
    std::cout << "What is the receiving device? (other than sending)" << std::endl;
    std::cin >> device2;
    std::cout << "Enter the message:" << std::endl;
    std::cin >> message;
    std::cout << "Choose protocol (Stop-and-Wait / Selective-Repeat):" << std::endl;
    std::cin >> protocol;

    // Apply access control and forward packets accordingly
    networkSwitch.applyAccessControl(protocol, deviceList[device].getMacAddress(), deviceList[device2].getMacAddress(), message);
    
    // Display MAC table and connected devices
    networkSwitch.displayConnectedDevices();
    // Simulate periodic refresh (add this after sending data)
   std::this_thread::sleep_for(std::chrono::seconds(5)); // Wait 5 seconds before refreshing
      networkSwitch.refreshMacTable();
     //networkSwitch.displayConnectedDevices();
  
}


       

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