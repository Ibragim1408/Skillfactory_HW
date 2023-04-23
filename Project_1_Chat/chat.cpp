#include "chat.h"
#include <iostream>

void Chat::start() {
	_isWorking = true;
	_forbiddenName.insert("all");
}

void Chat::showStartMenu() {
	while (true) {
		std::cout << "Choose option:\n";
		std::cout << "1 - Login\n";
		std::cout << "2 - Sign up\n";
		std::cout << "3 - Quit\n";
		char option;
		std::cin >> option;
		switch (option) {
			case '1':
				login();
				return;
			case '2':
				signUp();
				return;
			case '3':
				_isWorking = false;
				return;
			default:
				continue;
		}
	}
}

void Chat::showUserMenu() {
	while (true) {
		std::cout << "User Menu:\n Hi, " << _allUserInfo[_currentUser].getName() << ", please choose option!\n";
		std::cout << "1 - Show Message\n";
		std::cout << "2 - Send Message\n";
		std::cout << "3 - Users\n";
		std::cout << "9 - Sign Out" << std::endl;
		char option;
		std::cin >> option;
		switch (option) {
		case '1':
			showChat();
			return;
		case '2':
			sendMessage();
			return;
		case '3':
			showAllUsersName();
			break;
		case '9':
			_currentUser = 0;
			return;
		default:
			continue;
		}
	}
}

void Chat::login() {
	std::string login;
	std::string password;
	std::string name;
	std::cout << "Please, enter login, password and name:\n";
	std::cout << "Login: ";
	std::cin >> login;
	while (password.size() <= 4) {
		std::cout << "Password (more then 4 symbols): ";
		std::cin >> password;
	}
	std::cout << "Name: ";
	std::cin >> name;
	while (_forbiddenName.find(name) != _forbiddenName.end()) {
		std::cout << "Please, choose another name:\nName: ";
		std::cin >> name;
	}
	while (_allUsers.find(login) != _allUsers.end()) {
		std::cout << "Please, choose another login:\nLogin: ";
		std::cin >> login;
	}
	int newID = ++_lastId;
	_allUsers[login] = newID;
	_nameToLogin[name] = login;
	_allUserInfo[newID] = std::move(User(login, password, name));
	_currentUser = newID;
}

void Chat::signUp() {
	std::cout << "Please, enter login and password or q for exit to Start Menu:\n";
	std::string login;
	std::string password;	
	std::cout << "Login: ";
	std::cin >> login;
	if (login == "q") return;
	while (_allUsers.find(login) == _allUsers.end()) {
		std::cout << "Login not found:\nLogin: ";
		std::cin >> login;
	}
	int currentID = _allUsers[login];
	while (password.size() <= 4 || password != _allUserInfo[currentID].getPassword()) {
		std::cout << "Password( more then 4 symbols): ";
		std::cin >> password;
		if (password == "q") return ;
	}
	_currentUser = currentID;
}

void Chat::showChat() const {
	if (_allUserLoginMessageTo.find(_currentUser) != _allUserLoginMessageTo.end()) {
		for (const auto& message : _allUserLoginMessageTo.at(_currentUser)) {
			message.showMessage();
		}
	} else {
		std::cout << "No messages for you\n";
	}
}

void Chat::showAllUsersName() const {
	for (const auto& name : _allUserInfo) {
		std::cout << name.second.getName() << " ";
	}
	std::cout << std::endl;
}

void Chat::sendMessage() {
	std::string name;
	while (name.empty() || (name != "all" && _nameToLogin.find(name) == _nameToLogin.end())) {
		std::cout << "Choose name or send to all" << std::endl;
		std::cin >> name;
	}
	std::cout << "Enter the message:";
	std::string text;
	std::getline(std::cin, text);
	Message msg(_allUserInfo[_currentUser].getName(), name, text);
	if (name == "all") {
		for (auto& user : _allUsers) {
			_allUserLoginMessageTo[user.second].push_back(msg);
		}
	} else {
		int idTo = _allUsers[_nameToLogin[name]];
		_allUserLoginMessageTo[idTo].push_back(msg);
	}
}
