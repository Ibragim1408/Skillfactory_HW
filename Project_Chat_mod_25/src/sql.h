#pragma once 

#include <mysql.h>
#include <optional>

#include "user.h"
#include "message.h"


constexpr std::string kDB_NAME = "Chat_DB";
constexpr std::string kTB_USERS = "users";
constexpr std::string USERS_OPT = "id INT AUTO_INCREMENT PRIMARY KEY, username VARCHAR(255), login VARCHAR(255), password VARCHAR(255)";
constexpr std::string kTB_MESSAGES = "messages";
constexpr std::string MESSAGES_OPT = "id_msg INT AUTO_INCREMENT PRIMARY KEY, id_user_from INT, id_user_to INT, text VARCHAR(255), created_at TIMESTAMP";


MSQL CreateSQLConnection();
void CloseSQLConnection();

std::vector<std::pair<int, User>> SelectAllUsers();
std::optional<User> SelectUser(int id);
int InsertUser(int id, const User& user);

std::vector<Message> SelectAllMessages();
std::vector<Message> SelectMessagesTo(int id);
std::vector<Message> SelectMessagesFromTo(int id_to, int id_from);
int InsertMessage(const Message& msg);



