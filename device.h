#ifndef DEVICE_H
#define DEVICE_H
#include <string>
using namespace std;

class Devices {
private:
    string mac_address;
    string ip_address;

public:
    void setDevice(string mac_address, string ip_address);
    string getMacAddress() const;
    string getIpAddress() const;
};
#endif