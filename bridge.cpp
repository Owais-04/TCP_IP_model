
// #include "bridge.h"
// #include <iostream>

// void Bridge::connectSwitches(Switch* switch1, Switch* switch2) {
//     if (switch1 && switch2) {
//         // Connect the first port of the bridge to the first switch
//         ports[0] = switch1->getSwitch_mac;
//         switch1

//         // Connect the second port of the bridge to the second switch
//         ports[1] = switch2->getPort();
//         switch2->connectToBridge(this);

//         std::cout << "Bridge connected to two switches successfully." << std::endl;
//     } else {
//         std::cerr << "Error: One or both switches are null." << std::endl;
//     }
// }