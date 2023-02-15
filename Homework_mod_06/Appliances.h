#pragma once
#include "IElectronics.h"
class Appliances : virtual public IElectronics
{
public:
  Appliances(int weight);
  void ShowSpec() override;

private:
  int _weight;
};

