#include "devices.h"
#include <iostream>
using namespace std;


Device::Device(const string& mac, const string& ip)
    : mac_address(mac), ip_address(ip) {}

void Device::display() const {
    cout << "MAC Address: " << mac_address << "\nIP Address: " << ip_address << endl;
}


PC::PC(const string& mac, const string& ip, int ram, const string& cpu)
    : Device(mac, ip), ram(ram), cpu(cpu) {}

void PC::display() const {
    Device::display();
    cout << "RAM: " << ram << " GB\nCPU: " << cpu << endl;
}




Hub::Hub(const string& mac, const string& ip, int ports)
    : Device(mac, ip), ports(ports) {}

void Hub::display() const {
    Device::display();
    cout << "Ports: " << ports << endl;
}


Switch::Switch(const string& mac, const string& ip, int vlan_support)
    : Device(mac, ip), vlan_support(vlan_support) {}

void Switch::display() const {
    Device::display();
    cout << "VLAN Support: " << vlan_support << endl;
}
