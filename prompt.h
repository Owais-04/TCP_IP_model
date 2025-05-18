#include<iostream>
#include "topology.h"
#include "router.h"
#include "device.h"
using namespace std;
class prompt
{
    public :
    void layer1(){
        int choice;
        cout<<"enter the topology you want to use : (1 for star topoly, 2 for bus ) :"<<endl;
        cin>>choice;
        choose_Topology(choice);
    }
    void layer2(){
        int choice;
        cout<<"enter the topology you want to use(1. star 2. bus [uses token passing]) :"<<endl;
        cin>>choice;
        choose_Topology_layer2(choice);
        
    }
    void layer3(){
        int choice;
       cout<<"Select routing scheme:\n";
       cout<<"1: Static routing\n";
       cout<<"2: Dynamic routing\n";
       cin>>choice;
       choose_routing_scheme(choice);
    }
    void testcases(){
      int choice;
       cout<<"enter the layer you want to check test cases for :"<<endl;
       cin>>choice;
       switch(choice){
         case 1: testcases_layer1();
         break;
         case 2: testcases_layer2();
         break;
         default:
         cout<<"invalid choice"<<endl;
       }
       
    }
    void choose_routing_scheme(int choice){
        switch(choice){
            case 1:
            static_routing();
            break;
            case 2:
            dynamic_routing();
            break;
            default:
            cout<<"Invalid option\n";
        }
    }
    void static_routing() {
        cout << "=== Static Routing Simulation ===\n";
        
        // Create routers
        Router R1("R1", "192.168.1.1", "00:1A:2B:3C:4D:5E");
        Router R2("R2", "192.168.2.1", "00:1B:3C:4D:5E:6F");
        
        // Add static routes (example for /24 subnets)
        R1.addRoute("192.168.1.0/24", "192.168.1.1", 1);
        R1.addRoute("192.168.2.0/24", "192.168.2.1", 1);
        R2.addRoute("192.168.1.0/24", "192.168.1.1", 1);
        R2.addRoute("192.168.2.0/24", "192.168.2.1", 1);
        
        // Display routing tables
        R1.displayRoutingTable();
        R2.displayRoutingTable();
        
        // Ask for device numbers
        int senderIdx, receiverIdx;
        cout << "Enter sender device number (0-9): ";
        cin >> senderIdx;
        cout << "Enter receiver device number (0-9): ";
        cin >> receiverIdx;
        cin.ignore();

        // Extract IP addresses from deviceList
        string sourceIP = deviceList[senderIdx].getIpAddress();
        string destIP = deviceList[receiverIdx].getIpAddress();

        string data;
        cout << "Enter data to send: ";
        getline(cin, data);

        string protocol;
        cout << "Choose protocol (Stop-and-Wait/Selective-Repeat): ";
        getline(cin, protocol);

        // Now call sendPacket with IP addresses
        R1.sendPacket(sourceIP, destIP, data, protocol);
    }
    void dynamic_routing() {
        cout << "=== Dynamic Routing Simulation ===\n";
        // Implementation for dynamic routing (RIP, OSPF, etc.)
        cout << "Dynamic routing implementation coming soon...\n";
    }
    void custom_circuit(){
        int number;
       cout<<"What device you want to use \n1.hub \n2.switch"<<endl;
       cin>>number;
       switch(number){
          case 1:
             custom_circuit_layer1();
             break;
         case 2:
            custom_circuit_layer2();
            break;
            default:
            cout<<"invlaid"<<endl;
       }

    }
   
  
    void run(){
        initializeEndDevices();
        int x;
        cout << "1. for adding layer1 device\n"
             << "2. for layer2 device\n"
             << "3. for checking Test cases\n"
             << "4. custom ckt\n"
             << "5. for layer3 (routing)\n"
             << "Enter your choice: ";
        cin >> x;
        switch(x) {
            case 1:
                cout << "layer 1 device added : " << endl;
                layer1();
                break;
            case 2:
                cout << "layer 2 device added : " << endl;
                layer2();
                break;
            case 3:
                cout << "test cases for layer 1 and 2 :" << endl;
                testcases();
                break;
            case 4:
                cout << "custom created circuit :" << endl;
                custom_circuit();
                break;
            case 5:
                cout << "layer 3 (routing) simulation :" << endl;
                layer3();
                break;
            default:
                cout << "invalid choice" << endl;
        }
    }
};
