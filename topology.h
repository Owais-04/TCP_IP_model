#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <string>
using namespace std;

void choose_Topology(int x);
void choose_Topology_layer2(int x);
void hardwired_layer2();
void starTopology();
void starTopology_switch();
void busTopology();
void busTopology_access();
//void ringTopology();
void testcases_layer1();
void testcase1_layer1();
void testcase2_layer1();
void testcases_layer2();
void testcase1_layer2();
void testcase2_layer2();

void custom_circuit_layer1();
void custom_circuit_layer2();
void simulateNetworkCommunication(int senderDevice, int receiverDevice, const string& message);
#endif 
