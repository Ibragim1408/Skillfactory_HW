#include "chat.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <filesystem>

namespace fs = std::filesystem;

void Chat::start() {
	_isWorking = true;
	_forbiddenName.insert("all");
	_forbiddenName.insert("q");
	readFromFile();
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
				writeToFile();
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

void Chat::writeToFile() const {
	std::ofstream userFile( "output_user_file.txt");
	if (!userFile.is_open()) {
        std::cout << "Could not open userFile!" << '\n';
    } else {
        std::cout << "User File is Opened!" << '\n';
		for (const auto& users : _allUserInfo) {
			userFile << users.second << '\n';
		}
		userFile.close();
	}

	std::ofstream messageFile( "output_msg_file.txt");
	if (!messageFile.is_open()) {
        std::cout << "Could not open msgFile!" << '\n';
    } else {
        std::cout << "Message File is Opened!" << '\n';
		for (const auto& vMsgs : _allUserLoginMessageTo) {
			for (const auto& messages : vMsgs.second) {
				messageFile << messages << '\n';
			}
		}
		messageFile.close();
	}
}

void Chat::readFromFile() {
	std::fstream userFile( "output_user_file.txt");
	if (!userFile.is_open()) {
        std::cout << "Could not open userFile!" << '\n';
    } else {
		fs::permissions("output_user_file.txt",
        fs::perms::group_all | fs::perms::others_all, fs::perm_options::remove);

        std::cout << "User File is Opened!" << '\n';
		User user;
		while (	userFile >> user) {
			_nameToLogin[user.getName()] = user.getLogin();
			_allUsers[user.getName()] = ++_lastId;
			_allUserInfo[_lastId] = std::move(user);
		}
		userFile.close();
	}

	std::fstream messageFile( "output_msg_file.txt");
	if (!messageFile.is_open()) {
        std::cout << "Could not open msgFile!" << '\n';
    } else {
		fs::permissions("output_msg_file.txt",
        fs::perms::group_all | fs::perms::others_all, fs::perm_options::remove);

        std::cout << "Message File is Opened!" << '\n';
		Message msg;
		while(messageFile >> msg) {
			int to = _allUsers[msg.getTo()];
			_allUserLoginMessageTo[to].push_back(std::move(msg));
		}
		messageFile.close();
	}
}

bool Chat::ChangeUserStatus(const std::string& name, const std::string& st) {
	if (auto it = _nameToLogin.find(name); it != _nameToLogin.end()) {
		int id = _allUsers[it->second];
		_allUserInfo[id].setStatus(st);
		return true;
	}
	return false;
}

std::string Chat::GetAllMessages() const {
	std::stringstream result;
	for (const auto& [id, msgs] : _allUserLoginMessageTo) {
		for (const auto& msg : msgs) {
			result << msg << "\n";
		}
	}
	return result.str();
}

std::string Chat::GetAllUsers() const {
	std::stringstream result;
	for (const auto& [id, user] : _allUserInfo) {
		result << user.getName() << " " << user.getStatus() << "\n";
	}
	return result.str();
}