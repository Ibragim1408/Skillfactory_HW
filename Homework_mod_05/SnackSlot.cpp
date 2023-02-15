#include "SnackSlot.h"
SnackSlot::SnackSlot(int size) {
	snackType_ = new Snack[size];
	size_ = size;
	free_ = size;
}
SnackSlot::~SnackSlot() {
	delete[] snackType_;
}
void SnackSlot::addSnack(Snack* snack) {
	if (free_) {
		snackType_[size_ - free_] = *snack;
		--free_;
	}
	else {
		std::cout << "no free Space for new Snack - " << snack->getName() << std::endl;
	}
}
void SnackSlot::delSnack() {
	if (free_ == size_) {
		std::cout << "no Snack to delete" << std::endl;
	}
	else {
		std::cout << snackType_[size_ - free_ - 1].getName() << " is deleted" << std::endl;
		free_++;
	}
}