#pragma once
#include "SnackSlot.h"
#include <ostream>

class VendingMachine {
public:
	VendingMachine(int countSlots = 1);
	~VendingMachine();
	void addSlot(SnackSlot* slot);
	int getEmptySlotsCount() { return freeSlots_; };
private:
	int numSlots_;
	int freeSlots_;
	SnackSlot* slots_;
};

