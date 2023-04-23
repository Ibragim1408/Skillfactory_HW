#pragma once
#include <string>
#include <iostream>

struct Message {
public:
	Message(std::string from, std::string to, const std::string data)
		: _from(from), _to(to), _data(data) {};
	
	void showMessage() const {
	std::cout << "Message from: " << _from 
			  << " to: " << _to << "\n"
			  << "text: " << _data << std::endl;
	}
private:
	std::string _from;
	std::string _to;
	std::string _data;
};