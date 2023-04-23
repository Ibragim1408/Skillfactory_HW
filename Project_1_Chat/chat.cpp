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
		std::cout << "User Menu:\n";
		std::cout << "1 - Show Message\n";
		std::cout << "2 - Send Message\n";
		std::cout << "3 - Users\n";
		std::cout << "4 - Sign Out\n";
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
		case '4':
			_isWorking = false;
			return;
		default:
			continue;
		}
	}
}

void Chat::login() {

}

void Chat::signUp() {
	std::cout << "Please, enter login and password:\n";
	std::string login;
	std::string password;
	while (true) {
		std::cout << "Login: ";
		std::cin >> login;
		std::cout << "Password: ";
		std::cin >> password;

	}
}

void Chat::showchat() const {

}

void Chat::showAllUsersName() const {

}

void Chat::sendMessage() {

}
