#include <iostream>
#include "Phone.h"
#include "Fridge.h"
#include "Laptop.h"
#include <vector>

int main() {
	Phone phone1(7, "Iphone", 2013);
	Phone phone2(11, "Samsung", 2017);
	Phone phone3(18, "Huawei", 2020);

	Fridge fridge1(60, 40, 4);
	Fridge fridge2(80, 45, 6);
	Fridge fridge3(90, 120, 1);

	Laptop laptop1(24, 3, 17);
	Laptop laptop2(16, 2, 15);
	Laptop laptop3(12, 1, 13);

	vector<IElectronics*> ElStorages = { &phone1, &fridge1, &laptop1, &phone2, &fridge2, &laptop2, &phone3, &fridge3, &laptop3 };

	for (int i = 0; i < ElStorages.size(); i++) {
		ElStorages[i]->ShowSpec();
	}

	return 0;
}