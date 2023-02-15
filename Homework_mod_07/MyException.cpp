#include "MyException.h"

BadRange::BadRange(const char* msg) : _msg(msg) {}

const char* BadRange::what() const noexcept {
	return _msg.c_str();
}


BadLenght::BadLenght(const std::string& msg) : _msg(msg) {}

const char* BadLenght::what() const noexcept{
	return _msg.c_str();
}
