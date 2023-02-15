#include "Device.h"

Device::Device(int batteryLife) : _batteryLife(batteryLife)
{
}

void Device::ShowSpec()
{
  cout << "Battery Life: " << _batteryLife << endl;
}
