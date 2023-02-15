#pragma once
#include "IElectronics.h"

class Device : virtual public IElectronics {
public:
  Device(int batteryLife);
  virtual void ShowSpec() override;
private:
  int _batteryLife;
};

