#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sstream>

#include "helper.h"

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777 

struct sockaddr_in serveraddress, client;
socklen_t length;
int sockert_file_descriptor, connection, bind_status, connection_status;
char message[MESSAGE_LENGTH];

void create_connection();

int main() {
  Chat chat(ChatObject::kChatServer);
  chat.start();

  create_connection();

  while(chat.isWorking()) {
    bzero(message, MESSAGE_LENGTH);
    read(connection, message, sizeof(message));    
    if (strncmp("end", message, 3) == 0) {
      std::cout << "Client Exited." << std::endl;
      std::cout << "Server is Exiting..!" << std::endl;
      chat.closeChat();
      continue;
    }
    std::string msg(message);
    std::string answer = HandleMessage(chat, msg);
    bzero(message, MESSAGE_LENGTH);
    strcpy(message, answer.c_str());
    ssize_t bytes = write(connection, message, sizeof(message));
    // Если передали >= 0  байт, значит пересылка прошла успешно
    if(bytes >= 0)  {
      std::cout << "Data successfully sent to the client.!" << std::endl;
    }
  }

  close(sockert_file_descriptor);
  return 0;
}


void create_connection() {
  sockert_file_descriptor =  socket(AF_INET ,SOCK_STREAM, 0);
  if(sockert_file_descriptor == -1){
    std::cout << "Socket creation failed.!" << std::endl;
    exit(1);
  }
  serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
  // Зададим номер порта для связи
  serveraddress.sin_port = htons(PORT);
  // Используем IPv4
  serveraddress.sin_family = AF_INET;
  // Привяжем сокет
  bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress,
  sizeof(serveraddress));
  if(bind_status == -1)  {
    std::cout << "Socket binding failed.!" << std::endl;
    exit(1);
  }
  // Поставим сервер на прием данных 
  connection_status = listen(sockert_file_descriptor, 5);
  if(connection_status == -1) {
    std::cout << "Socket is unable to listen for new connections.!" << std::endl;
    exit(1);
  } else {
    std::cout << "Server is listening for new connection: " << std::endl;
  }
  length = sizeof(client);
  connection = accept(sockert_file_descriptor,(struct sockaddr*)&client, &length);
  if(connection == -1)  {
    std::cout << "Server is unable to accept the data from client.!" << std::endl;
    exit(1);
  }
}