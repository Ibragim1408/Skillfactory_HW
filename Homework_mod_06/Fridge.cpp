#include "Fridge.h"

Fridge::Fridge(int weight, int volume, int section)
	: Appliances(weight), _volume(volume), _section(section)
{
}

void Fridge::ShowSpec()  {
	cout << "Fridge's characteristics:\n";
	Appliances::ShowSpec();
	cout << "Overall volume: " << _volume << " with " << _section << " section\n";
}