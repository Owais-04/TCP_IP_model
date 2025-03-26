#include<iostream>
#include "topology.h"
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
        cout<<"1. for adding layer1 device \n2. for layer2 device \n3. for checking Test cases:\n4. custom ckt "<<endl;
        cin>>x;
        switch(x){
            case 1:
            cout<<"layer 1 device added : "<<endl;
            layer1();
            break;
            case 2:
            cout<<"layer 2 device added : "<<endl;
            layer2();
            break;
            case 3:
            cout<<"test cases for layer 1 and 2 :"<<endl;
            testcases();
            break;
            case 4:
            cout<<"custom created circut :"<<endl;
            custom_circuit();
            break;
            default:
            cout<<"invalid "<<endl;
        }

    }
};
