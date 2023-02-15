#include "Laptop.h"

Laptop::Laptop(int batteryLife, int weight, int diagonal)
	: Device(batteryLife), Appliances(weight), _diagonal(diagonal) 
{
}

void Laptop::ShowSpec() {
	cout << "Laptop's characteristic:\n";
	Appliances::ShowSpec();
	Device::ShowSpec();
	cout << "Diagonal: " << _diagonal << endl;
}