#pragma once
#include <fstream>
#include <string>

class User {
public:
	User() : _login(""), _password("1234"), _name("") {};
	User(const std::string& login, const std::string& pass, const std::string& name, const std::string& st = "unban")
		: _login(login), _password(pass), _name(name), _status(st) {};

	const std::string& getLogin() const { return _login; };
	
	const std::string& getPassword() const { return _password; };
	void changePassword(const std::string& newPassword) { _password = newPassword; };

	const std::string& getName() const { return _name; };
	void changeName(const std::string& newName) { _name = newName; };

	void setStatus(const std::string& st) {_status = st;}
	std::string getStatus() const {return _status;}

	friend std::fstream& operator >>(std::fstream& is, User& obj);
	friend std::ostream& operator <<(std::ostream& os, const User& obj);

private:
	std::string _login;
	std::string _password;
	std::string _name;
	std::string _status = "unban";
};
