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
		std::cout << toString();
	}

	std::string toString() const;
	std::string getTo() const {return _to;}
	std::string getFrom() const {return _from;}

	friend std::fstream& operator >>(std::fstream& is, Message& obj);
	friend std::ostream& operator <<(std::ostream& os, const Message& obj);

private:
	std::string _from;
	std::string _to;
	std::string _data;
};
