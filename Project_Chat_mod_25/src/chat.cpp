#include "chat.h"
#include "sql.h"
#include <iostream>
#include <sstream>
#include <filesystem>


int Chat::createUser(const std::string& login, const std::string& password, const std::string& name) {
	if (_forbiddenName.find(name) != _forbiddenName.end()) {
		return -1;
	}
	if (_allUsers.find(login) != _allUsers.end()) {
		return -1;
	}
	if (_nameToLogin.find(name) != _nameToLogin.end()) {
		return -1;
	}
	int newID = ++_lastId;
	_allUsers[login] = newID;
	_nameToLogin[name] = login;
	InsertUser(newID, User(login, password, name));
	_currentUser = newID;
	return newID;
}

int Chat::login(const std::string& login, const std::string& password){
	if (login == "q") return -1;
	if (_allUsers.find(login) == _allUsers.end()) {
		return -1;
	}
	int currentID = _allUsers[login];
	if (auto user = SelectUser(currentID); user.has_value() && password != user.value().getPassword()) {
		return -1;
	}
	_currentUser = currentID;
	return currentID;
}

int Chat::sendMessage(const std::string& name_from, const std::string& name_to, const std::string& text) {
	if (name_to != "all" && _nameToLogin.find(name_to) == _nameToLogin.end()) {
		return -1;
	}
	int currentID = _allUsers[_nameToLogin[name_from]];
	if (name_to == "all") {
		for (const auto& [name, login] : _nameToLogin) {
			if (name_from == name) continue;
			Message msg(name_from, name, text);
			InsertMessage(msg);
		}
	} else {
		Message msg(name_from, name_to, text);
		InsertMessage(msg);
	}
	return 1;
}

std::string Chat::getUserList() {
	std::stringstream stream;
	for (const auto& name : _nameToLogin) {
		stream << name.first << " ";
	}
	return stream.str();
}

std::vector<Message> Chat::getMessageFrom(const std::string& name_current, const std::string& name_from) {
	int current_id = _allUsers[_nameToLogin[name_current]];
	int id_from = _allUsers[_nameToLogin[name_from]];
	return SelectMessagesFromTo(current_id, id_from);
}

std::vector<Message> Chat::getMessageFromAll(const std::string& name_current) {
	int current_id = _allUsers[_nameToLogin[name_current]];
	return SelectMessagesTo(current_id);
}

bool Chat::isNameExist(const std::string &name) {
    return (_nameToLogin.find(name) != _nameToLogin.end());
}

void Chat::closeChat() {
	//writeToFile();
    mysql_close(&_mysql);
    _isWorking = false;
}

void Chat::start() {
	_isWorking = true;
	_forbiddenName.insert("all");
	_forbiddenName.insert("q");
	if (_type == ChatObject::kChatServer) {
		CreateSQLConnection(_mysql);
	}
	readFromDB();
}

std::pair<ActionType, std::string> Chat::showStartMenu() {
	while (true) {
		std::cout << "Choose option:\n";
		std::cout << "1 - Create User\n";
		std::cout << "2 - Log In\n";
		std::cout << "3 - Quit\n";
		char option;
		std::cin >> option;
		switch (option) {
			case '1':
				return std::make_pair(ActionType::kCreateUser, clientCreateUser());
			case '2':
				return std::make_pair(ActionType::kLoginUser, logIn());
			case '3':
				_isWorking = false;
				return std::make_pair(ActionType::kCloseChat, "");
			default:
				continue;
		}
	}
}

std::pair<ActionType, std::string> Chat::showUserMenu() {
	while (true) {
		std::cout << "User Menu:\n Hi, " << SelectUser(_currentUser).value().getName() << ", please choose option!\n";
		std::cout << "1 - Show Message From\n";
		std::cout << "2 - Send Message\n";
		std::cout << "3 - Users\n";
		std::cout << "4 - Show All Message to Me";
		std::cout << "9 - Sign Out" << std::endl;
		char option;
		std::cin >> option;
		switch (option) {
		case '1':
			return std::make_pair(ActionType::KRecieveMessageFrom, showChatFrom());
		case '2':
			return std::make_pair(ActionType::kSendMessage, sendMessageTo());
		case '3':
			return std::make_pair(ActionType::kUserList, "userList");
		case '4':
			return std::make_pair(ActionType::kRecieveAllMessage, "message from all");
		case '9':
			_currentUser = 0;
			return std::make_pair(ActionType::kSendMessage, "");;
		default:
			continue;
		}
	}
}

std::string Chat::clientCreateUser() {
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
	std::stringstream stream;
	stream << login << "$$" << password << "$$" << name;
	return stream.str();
}

std::string Chat::logIn() {
	std::cout << "Please, enter login and password or q for exit to Start Menu:\n";
	std::string result;
	std::string password;
	std::cout << "Login: ";
	std::cin >> result;
	if (result == "q") {
		return "";
	}
	while (password.size() <= 4 ) {
		std::cout << "Password( more then 4 symbols): ";
		std::cin >> password;
		if (password == "q") return "";
	}
	result += "$$" + password;
	return result;
}

std::string Chat::showChatFrom() const {
	std::cout << "Please, enter NAME to see messages from this User:\n";
	std::string result;
	std::cin >> result;
	return result;
}

std::string Chat::sendMessageTo() {
	std::string name;
	while (name.empty() || (name != "all")) {
		std::cout << "Choose name or send to all" << std::endl;
		std::cin >> name;
	}
	std::cout << "Enter the message:";
	std::string text;
	std::getline(std::cin, text);
	return name + "&&" + text;
}

void Chat::readFromDB() {
	const auto& res = SelectAllUsers();
	for (const auto& [id, user] : res) {
		_nameToLogin[user.getName] = user.getLogin();
		_allUsers[user.getLogin()] = id;
	}
}
