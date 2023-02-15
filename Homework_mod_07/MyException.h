#pragma once

#include <stdexcept>
#include <string>

class BadRange : public std::exception {
public:
	BadRange(const char* msg);
	virtual const char* what() const noexcept override;
protected:
	std::string _msg;
};

class BadLenght : public std::exception {
public:
	BadLenght(const std::string& msg);
	virtual const char* what() const noexcept override;
protected:
	std::string _msg;
};

