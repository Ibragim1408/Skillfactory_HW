#pragma once
#include <string>
#include <fstream>
#include <iostream>

struct Message {
public:
	Message() {};
	Message(std::string from, std::string to, const std::string data)
		: _from(from), _to(to), _data(data) {};
	
	void showMessage() const {
	std::cout << "Message from: " << _from 
			  << " to: " << _to << "\n"
			  << "text: " << _data << std::endl;
	}

	std::string getTo() const {return _to;}

	friend std::fstream& operator >>(std::fstream& is, Message& obj);
	friend std::ostream& operator <<(std::ostream& os, const Message& obj);

private:
	std::string _from;
	std::string _to;
	std::string _data;
};
