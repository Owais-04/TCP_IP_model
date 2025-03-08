#ifndef DEVICE_H
#define DEVICE_H
#include <string>

using namespace std;

class Devices {
private:
    string mac_address;
    string ip_address;

public:
    void setDevice(const string& mac_address, const string& ip_address);
    string getMacAddress() const;
    string getIpAddress() const;
};

void initializeDevices();
#endif