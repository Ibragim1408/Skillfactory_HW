#include "Phone.h"

Phone::Phone(int batteryLife, string model, int generation)
	: Device(batteryLife), _model(model), _generation(generation) 
{
}

void Phone::ShowSpec()
{
	cout << _model << " gen. " << _generation << " ";
	Device::ShowSpec();
}
