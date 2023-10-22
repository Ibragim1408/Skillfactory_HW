#include "sql.h"

#include <iostream>
#include <format>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <string>

void CreateDB(MYSQL& mysql) {
    auto *result = mysql->executeQuery("SHOW DATABASES");
    bool db_exists = false;
    // Перебираем строки результата
    while (result->next()) {
        std::string db_name = result->getString(1);
        if (db_name == kDB_NAME) {
            db_exists = true;
            break;
        }
    }
    if (!db_exists && !mysql_query(&mysql, std::format("CREATE DATABASE {}", kDB_NAME).c_str())) {
        std::cout << std::format("Ошибка создания базы данных: {}\n", mysql_error(&mysql)).c_str();
    }
}

void CreateTable(MYSQL& mysql, const std::string& table_name, const std::string& table_options) {
    auto *result = mysql->executeQuery("SHOW TABLES");
    bool tb_exists = false;
    // Перебираем строки результата
    while (result->next()) {
        std::string tb_name = result->getString(1);
        if (tb_name == table_name) {
            tb_exists = true;
            break;
        }
    }
    if (!tb_exists) {
        mysql_query(&mysql, std::format("CREATE TABLE {}({})", table_name, table_options).c_str());
    }     
}


bool CreateSQLConnection(MYSQL& mysql) {
    mysql_init(&mysql);

    if (!mysql_real_connect(&mysql, "localhost", "root", "root", NULL, 0, NULL, 0)) {
        printf("Ошибка подключения: %s\n", mysql_error(&mysql));
        return false;
    }
    if (!CreateDB(mysql)) {
        return false;
    }
    mysql_set_character_set(&mysql, "utf8");
    CreateTable(mysql, kTB_USERS, USERS_OPT);
    CreateTable(mysql, kTB_MESSAGES, MESSAGES_OPT);
    return true;
}

std::vector<std::pair<int, User>> SelectAllUsers() {
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(&mysql, std::format("SELECT * FROM {}", kTB_USERS).c_str());
    std::vector<std::pair<int, User>> result;
    if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
            result.emplace_back(row[0], User(row[2], row[3], row[1]));
		}
	}
    return result;
}

std::optional<User> SelectUser(int id) {
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(&mysql, std::format("SELECT * FROM {} WHERE id={}", kTB_USERS,id).c_str());
    if (res = mysql_store_result(&mysql)) {
		row = mysql_fetch_row(res);
        return User(row[2], row[3], row[1]);
	}
    return std::nullopt;
}

int SelectUserByName(std::string name) {
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(&mysql, std::format("SELECT * FROM {} WHERE username='{}'", kTB_USERS, name).c_str());
    if (res = mysql_store_result(&mysql)) {
		row = mysql_fetch_row(res);
        return std::atoi(row[0]);
	}
    return -1;
}


int InsertUser(int id, const User& user) {
    return mysql_query(&mysql, std::format("INSERT INTO {}(id, username, login, password) values({}, {}, {}, {}')",
                kTB_USERS, id, user.getName(), user.getLogin(), user.getPassword()).c_str());
}

std::vector<Message> SelectAllMessages() {
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(&mysql, std::format("SELECT * FROM {}", kTB_MESSAGES).c_str());
    std::vector<Message> result;
    if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
            result.push_back(Message(row[1], row[2], row[3]));
		}
	}
    return result;
}

std::vector<Message> SelectMessagesTo(int id) {
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(&mysql, std::format("SELECT * FROM {} WHERE id_user_to='{}'", kTB_MESSAGES, id).c_str());
    std::vector<Message> result;
    if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
            result.push_back(Message(row[1], row[2], row[3]));
		}
	}
    return result;
}
std::vector<Message> SelectMessagesFromTo(int id_to, int id_from) {
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(&mysql, std::format("SELECT * FROM {} WHERE id_user_to='{}' AND id_user_from='{}'", 
                                    kTB_MESSAGES, id_to, id_from).c_str());
    std::vector<Message> result;
    if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
            result.push_back(Message(row[1], row[2], row[3]));
		}
	}
    return result;
}

int InsertMessage(const Message& msg) {
    int id_from = SelectUserByName(msg.getFrom());
    int  id_to = SelectUserByName(msg.getTo());
    auto start = std::chrono::system_clock::now();
    std::string timestamp = std::to_string(start);
    return mysql_query(&mysql, std::format("INSERT INTO {}(id_msg, id_user_from, id_user_to, text, created) values(default, {}, {}, {}, {}')",
                kTB_MESSAGES,  id_from, id_to, msg.getText(), timestamp).c_str());
}

