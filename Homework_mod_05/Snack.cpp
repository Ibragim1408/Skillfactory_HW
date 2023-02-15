#include "Snack.h"

Snack::Snack(const std::string& name) {
	name_ = name;
	price_ = 0;
}


Snack::Snack(const std::string& name, unsigned int price) {
	name_ = name;
	price_ = price;
}

Snack::Snack(const Snack& other) {
	name_ = other.name_;
	price_ = other.price_;
}

std::string Snack::getName() {
	return name_;
}

void Snack::setName(const std::string& name) {
	name_ = name;
}

unsigned int Snack::getPrice() {
	return price_;
}

void Snack::setPrice(unsigned int newPrice) {
	price_ = newPrice;
}
