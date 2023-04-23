#pragma once
#include "user.h"
#include "message.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <forward_list>


class Chat {
public:

	void start();
	bool isWorking() const { return _isWorking; };
	void showStartMenu();
	bool getCurrentUser() const { return _currentUser; };
	void showUserMenu();

private:
	int _lastId_ = 0;
	int _currentUser = 0;
	bool _isWorking = false;
	
	std::unordered_set<std::string> _forbiddenName;
	std::unordered_map<std::string, int> _allUsers;			// [login, id]
	std::unordered_map<int, User> _allUserInfo;					// [id, Users]
	std::unordered_map<int, std::forward_list<std::string>> _allUserLoginMessageTo;   // [login, list<message_to>]
	std::unordered_map<int, std::forward_list<std::string>> _allUserLoginMessageFrom; // [login, list<message_from>]

	void login();
	void signUp();
	void showchat() const;
	void showAllUsersName() const;
	void sendMessage();
};