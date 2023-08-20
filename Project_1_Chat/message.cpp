#include "message.h"

std::fstream& operator>>(std::fstream& is, Message& obj) {
	is >> obj._from >> obj._to >> obj._data;
	return is;
}

std::ostream& operator <<(std::ostream& os, const Message& obj) {
	os << obj._from << ' ';
	os << obj._to << ' ';
	os << obj._data;
	return os;
}
