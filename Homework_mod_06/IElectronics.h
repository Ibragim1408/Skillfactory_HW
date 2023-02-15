#pragma once 

#include <iostream>
using namespace std;

class IElectronics {
public:
  virtual void ShowSpec() = 0;
  virtual ~IElectronics() = default;
};