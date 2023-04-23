#pragma once
#include <string>

class User {
public:
	User() : _login(""), _password("1234"), _name("") {};
	User(const std::string& login, const std::string& pass, const std::string name)
		: _login(login), _password(pass), _name(name) {};

	const std::string& getLogin() const { return _login; };
	
	const std::string& getPassword() const { return _password; };
	void changePassword(const std::string& newPassword) { _password = newPassword; };

	const std::string& getName() const { return _name; };
	void changeName(const std::string& newName) { _name = newName; };

private:
	std::string _login;
	std::string _password;
	std::string _name;
};