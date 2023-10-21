#pragma once

#include "chat.h"

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

ActionType ToActionType(std::string_view sw);
std::string ToString(ActionType act);



std::string HandleMessage(Chat& chat, std::string& msg);

