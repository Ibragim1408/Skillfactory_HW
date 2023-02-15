#pragma once
#include "Appliances.h"
class Fridge : public Appliances
{
public:
	Fridge(int weight, int volume, int section);
	void ShowSpec() override;
private:
	int _volume;
	int _section;
};

