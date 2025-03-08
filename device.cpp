#include "device.h"

void Devices::setDevice(string mac_address, string ip_address) {
    this->mac_address = mac_address;
    this->ip_address = ip_address;
}

string Devices::getMacAddress() const {
    return mac_address;
}

string Devices::getIpAddress() const {
    return ip_address;
}