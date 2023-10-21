#include "helper.h"
#include <sstream>

std::vector<std::string> Split(const std::string s, const std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back(s.substr (pos_start));
    return res;
}

  // получаем запросы от клиента:
  // 0 - создать пользователя
  // 1 - залогиниться
  // 2 - отправить сообщение кому-то - сохранить сообщение в объекте класса
  // 3 - получить список пользователей - ???
  // 4 - посмотреть сообщения от ***
  // 5 - получить историю сообщение

std::string HandleCreateUser(Chat& chat, const std::vector<std::string>& parseMsg) {
    if (parseMsg.size() != 4) {
        return "-1";
    }
	if (parseMsg[2].size() <= 4) {
		return "-1";
	}
    return std::to_string(chat.createUser(parseMsg[1], parseMsg[2], parseMsg[3])); // login, pass, name;
}

std::string HandleLoginUser(Chat& chat, const std::vector<std::string>& parseMsg) {
    if (parseMsg.size() != 3) {
        return "-1";
    }
    if (parseMsg[2].size() <= 4) {
		return "-1";
	}
    return std::to_string(chat.login(parseMsg[1], parseMsg[2])); // login, pass;  
}

std::string HandleSendMessage(Chat& chat, const std::vector<std::string>& parseMsg) {
    if (parseMsg.size() != 4) {
        return "-1";
    }
    if (parseMsg[2].empty()) {
        return "-1";
    }
    return std::to_string(chat.sendMessage(parseMsg[1], parseMsg[2], parseMsg[3])); // name_from, name_to or all, message;  
}

std::string HandleListMessage(Chat& chat, const std::vector<std::string>& parseMsg, bool fromAll) {
    if (parseMsg.size() != 3 - fromAll) {
        return "-1";
    }
    if (parseMsg[2].empty()) {
        return "-1";
    }
    std::stringstream stream;
    std::vector<Message> result;
    if (fromAll) {
        result = std::move(chat.getMessageFromAll(parseMsg[1])); // current
    } else {
        result = std::move(chat.getMessageFrom(parseMsg[1], parseMsg[2])); // current, from
    }
    for (const auto& message : result) {
        stream << message.toString();
    }
    return stream.str();
}



std::string HandleMessage(Chat& chat, std::string& msg) {
    if (msg.empty()) {
        chat.closeChat();
        return msg;
    }
    std::vector<std::string> parseMsg = Split(msg, "$$");
    ActionType command = ToActionType(parseMsg[0]);

    switch (command) {
		case ActionType::kCreateUser:
            return HandleCreateUser(chat, parseMsg);
		case ActionType::kLoginUser:
            return HandleLoginUser(chat, parseMsg);
		case ActionType::kSendMessage:
			return HandleSendMessage(chat, parseMsg);
		case ActionType::kUserList:
			return chat.getUserList();
		case ActionType::KRecieveMessageFrom:
			return HandleListMessage(chat, parseMsg, false);
		case ActionType::kRecieveAllMessage:
			return HandleListMessage(chat, parseMsg, true);
		case ActionType::kCloseChat:
            chat.closeChat();
			return "";
		case ActionType::kUnknownCommand:
			return "Unknown";
  }
}


ActionType ToActionType(std::string_view sw) {
	if (sw == "CreateUser") {
		return ActionType::kCreateUser;
	}
	if (sw == "LoginUser") {
		return ActionType::kLoginUser;
	}
	if (sw == "SendMessage") {
		return ActionType::kSendMessage;
	}
	if (sw == "UserList") {
		return ActionType::kUserList;
	}
	if (sw == "RecMsgFrom") {
		return ActionType::KRecieveMessageFrom;
	}
	if (sw == "RecAllMsg") {
		return ActionType::kRecieveAllMessage;
	}
	if (sw == "CloseChat") {
		return ActionType::kCloseChat;
	}
	return ActionType::kUnknownCommand;
}

std::string ToString(ActionType act) {
    switch (act) {
		case ActionType::kCreateUser:
			return "CreateUser";
		case ActionType::kLoginUser:
			return "LoginUser";
		case ActionType::kSendMessage:
			return "SendMessage";
		case ActionType::kUserList:
			return "UserList";
		case ActionType::KRecieveMessageFrom:
			return "RecMsgFrom";
		case ActionType::kRecieveAllMessage:
			return "RecAllMsg";
		case ActionType::kCloseChat:
			return "CloseChat";
		case ActionType::kUnknownCommand:
			return "Unknown";
	}
}