#pragma once
#include "user.h"
#include "message.h"
#include <unordered_map>
#include <unordered_set>

#include <vector>


class Chat {
public:
	Chat() : _lastId(0), _currentUser(0), _isWorking(false) {};
	void start();
	bool isWorking() const { return _isWorking; };
	void showStartMenu();
	int getCurrentUser() const { return _currentUser; };
	void showUserMenu();
	
private:
	int _lastId;
	int _currentUser;
	bool _isWorking;
	
	std::unordered_set<std::string> _forbiddenName;
	std::unordered_map<std::string, std::string> _nameToLogin;	// [name, login]
	std::unordered_map<std::string, int> _allUsers;				// [login, id]
	std::unordered_map<int, User> _allUserInfo;					// [id, Users]
	std::unordered_map<int, std::vector<Message> > _allUserLoginMessageTo;   // [id, list<message_to>]
//  std::unordered_map<int, std::vector<Message>> _allUserLoginMessageFrom; // [login, list<message_from>] - может в дальнейшем пригодится

	void login();
	void signUp();
	void showChat() const;
	void showAllUsersName() const;
	void sendMessage();

	void writeToFile() const;
	void readFromFile();
};