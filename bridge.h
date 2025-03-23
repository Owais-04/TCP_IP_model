// #include "switch.h"
// #ifndef BRIDGE_H
// #define BRIDGE_H

// #include "device.h"
// #include <unordered_map>

// class Bridge  {
//   private:
//   string mac_address;
//   int portnumber=2;
//   vector<Switch*> connectedDevices;
//   unordered_map<int ,Switch*>portvsmactable;
//   public:
//   void connectSwitches(Switch* device);
//   void forwardData(const int inputport, const int  outputport, const string& data);
//   void displayMacvsport() const;
// };

// #endif // BRIDGE_H