#include "VendingMachine.h"

VendingMachine::VendingMachine(int countSlots) {
	numSlots_ = countSlots;
	freeSlots_ = numSlots_;
	slots_ = new SnackSlot[numSlots_];
}

VendingMachine::~VendingMachine() {
	delete[] slots_;
}

void VendingMachine::addSlot(SnackSlot* slot) {
	if (freeSlots_ > 0)
		slots_[numSlots_ - freeSlots_ + 1] = *slot;
	else {
		std::cout << "No free Slots for adding" << '\n';
	}
}
