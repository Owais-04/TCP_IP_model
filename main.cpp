#include <iostream>
#include <vector>
#include "device.h"
#include "topology.h"
#include "paramhs.h"


using namespace std;

int main() {
    
    initializeDevices();//check this function in device.cpp

    for (int i = 0; i < deviceList.size(); i++) {
        cout << "Device " << i + 1 << " - MAC: " 
             << deviceList[i].getMacAddress() 
             << ", IP: " << deviceList[i].getIpAddress() << endl;
    }
   
    choose_Topology(2);

   
    return 0;
}
