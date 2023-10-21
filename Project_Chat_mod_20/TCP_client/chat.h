#pragma once
#include "user.h"
#include "message.h"
#include <unordered_map>
#include <unordered_set>

#include <vector>

enum class ChatObject {
	kChatServer,
	kChatClient
};

class Chat {
public:
	Chat(ChatObject type) : _type(type), _lastId(0), _currentUser(0), _isWorking(false) {};
	void start();
	bool isWorking() const { return _isWorking; };
	void showStartMenu();
	int getCurrentUser() const { return _currentUser; };
	void showUserMenu();
	// Actions:
	int createUser(const std::string& login, const std::string& password, const std::string& name);
	int login(const std::string& login, const std::string& password);
	int sendMessage(const std::string& login_from, const std::string& name_to, const std::string& text);
	std::string getUserList();
	std::vector<Message> getMessageFrom(const std::string& name_current, const std::string& name_from);
	std::vector<Message> getMessageFromAll(const std::string& name_current);

	bool isNameExist(const std::string& name);
	void closeChat();
private:
	ChatObject _type;
	int _lastId;
	int _currentUser;
	bool _isWorking;
	
	std::unordered_set<std::string> _forbiddenName;
	std::unordered_map<std::string, std::string> _nameToLogin;	// [name, login]
	std::unordered_map<std::string, int> _allUsers;				// [login, id]
	std::unordered_map<int, User> _allUserInfo;					// [id, Users]
	std::unordered_map<int, std::vector<Message> > _allUserLoginMessageTo;   // [id, list<message to id>]
//  std::unordered_map<int, std::vector<Message>> _allUserLoginMessageFrom; // [login, list<message_from>] - может в дальнейшем пригодится

	void login();
	void signUp();
	void showChat() const;
	void showAllUsersName() const;
	void sendMessage();

	void writeToFile() const;
	void readFromFile();
};