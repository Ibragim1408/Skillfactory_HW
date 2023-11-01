#pragma once 

#include <mysql/mysql.h>
#include <optional>
#include <vector>
#include <string_view>
#include "user.h"
#include "message.h"


constexpr std::string_view kDB_NAME = "Chat_DB";
constexpr std::string_view kTB_USERS = "users";
constexpr std::string_view USERS_OPT = "id INT AUTO_INCREMENT PRIMARY KEY, username VARCHAR(255), login VARCHAR(255), password VARCHAR(255)";
constexpr std::string_view kTB_MESSAGES = "messages";
constexpr std::string_view MESSAGES_OPT = "id_msg INT AUTO_INCREMENT PRIMARY KEY, id_user_from INT, id_user_to INT, text VARCHAR(255), created_at TIMESTAMP";


bool CreateSQLConnection(MYSQL& mysql);

std::vector<std::pair<int, User>> SelectAllUsers(MYSQL& mysql);
std::optional<User> SelectUser(int id, MYSQL& mysql);
int InsertUser(int id, const User& user, MYSQL& mysql);

std::vector<Message> SelectAllMessages(MYSQL& mysql);
std::vector<Message> SelectMessagesTo(int id, MYSQL& mysql);
std::vector<Message> SelectMessagesFromTo(int id_to, int id_from, MYSQL& mysql);
int InsertMessage(const Message& msg, MYSQL& mysql);
