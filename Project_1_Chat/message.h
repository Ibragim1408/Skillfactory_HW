#pragma once
#include <string>

class Message {
public:
	Message(int from, int to, const std::string data)
		: _from(from), _to(to), _data(data) {};
private:
	int _from;
	int _to;
	std::string _data;
};