#pragma once
#include "Device.h"
#include "Appliances.h"

class Laptop : public Device, Appliances 
{
public:
	Laptop(int batteryLife, int weight, int diagonal);
	void ShowSpec() override;
private:
	int _diagonal;
};

