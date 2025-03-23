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
        cout<<"enter the topology you want to use : (1 for star topoly, 2 for hybrid topology ) :"<<endl;
        cin>>choice;
        choose_Topology_layer2(choice);
        
    }
    void run(){
        initializeEndDevices();
        int x;
        cout<<"enter the layer device you want to add: "<<endl;
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
        }

    }
};
