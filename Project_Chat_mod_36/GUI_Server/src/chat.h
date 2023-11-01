#pragma once
#include "user.h"
#include "message.h"
#include "sql.h"
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <vector>

enum class ActionType {
	kCreateUser,         // 0 - создать пользователя
	kLoginUser,          // 1 - залогиниться
	kSendMessage,        // 2 - отправить сообщение кому-то
	kUserList,     		 // 3 - получить список пользователей
	KRecieveMessageFrom, // 4 - посмотреть сообщения от ***
	kRecieveAllMessage,  // 5 - получить историю сообщение
	kCloseChat,			 // 6 - завершить чат
	kUnknownCommand
};

enum class ChatObject {
	kChatServer,
	kChatClient
};

class Chat {
public:
	Chat(ChatObject type) : _type(type), _lastId(0), _currentUser(0), _isWorking(false) {};
	void start();
	bool isWorking() const { return _isWorking; };
	int getCurrentUser() const { return _currentUser; };
	void setCurrentUser(int id) {_currentUser = id;};

	// Client Actions:
	std::pair<ActionType, std::string> showStartMenu();
	std::pair<ActionType, std::string> showUserMenu();
	// Server Actions:
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
	MYSQL _mysql;
	
	std::unordered_set<std::string> _forbiddenName;
	std::unordered_map<std::string, std::string> _nameToLogin;	// [name, login]
	std::unordered_map<std::string, int> _allUsers;				// [login, id]
	// std::unordered_map<int, User> _allUserInfo;					// [id, Users]
	// std::unordered_map<int, std::vector<Message> > _allUserLoginMessageTo;   // [id, list<message to id>]
	// std::unordered_map<int, std::vector<Message>> _allUserLoginMessageFrom; // [login, list<message_from>] - может в дальнейшем пригодится

	std::string clientCreateUser();
	std::string logIn();
	std::string showChatFrom() const;
	//void showAllUsersName() const;
	std::string sendMessageTo();

//	void writeToFile() const;
	void readFromDB();
};