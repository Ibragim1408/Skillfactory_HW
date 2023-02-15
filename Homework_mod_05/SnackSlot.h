#pragma once
#include "Snack.h"
#include <iostream>

class SnackSlot {
public:
	SnackSlot(int size = 1);
	~SnackSlot();
	void addSnack(Snack* snack);
	void delSnack();
private:
	Snack* snackType_;
	int size_, free_;

};

