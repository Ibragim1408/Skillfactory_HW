#pragma once
#include "Device.h"


class Phone : public Device
{
public:
	Phone(int batteryLife, string model, int generation);
	void ShowSpec() override;
private:
	string _model;
	int _generation;
};

