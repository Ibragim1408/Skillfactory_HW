#pragma once
#include <string>

class Snack {
public:
	Snack() = default;
	Snack(const std::string& name);
	Snack(const std::string& name, unsigned int price);

	Snack(const Snack& other);

	std::string getName();
	void setName(const std::string& name);
	unsigned int getPrice();
	void setPrice(unsigned int newPrice);
private:
	std::string name_;
	unsigned int price_;
};

