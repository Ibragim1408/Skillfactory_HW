#include "Appliances.h"

Appliances::Appliances(int weight) : _weight(weight)
{
}

void Appliances::ShowSpec()
{
  cout << "Weight: " << _weight << endl;
}