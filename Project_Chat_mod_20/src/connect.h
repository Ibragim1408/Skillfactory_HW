#pragma once
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>

#include<iostream>

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777 

struct sockaddr_in serveraddress, client;
socklen_t length;
int socket_file_descriptor, connection, bind_status, connection_status;
char message[MESSAGE_LENGTH];

void create_server_connection() {
  socket_file_descriptor =  socket(AF_INET ,SOCK_STREAM, 0);
  if(socket_file_descriptor == -1){
    std::cout << "Socket creation failed.!" << std::endl;
    exit(1);
  }
  serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
  // Зададим номер порта для связи
  serveraddress.sin_port = htons(PORT);
  // Используем IPv4
  serveraddress.sin_family = AF_INET;
  // Привяжем сокет
  bind_status = bind(socket_file_descriptor, (struct sockaddr*)&serveraddress,
  sizeof(serveraddress));
  if(bind_status == -1)  {
    std::cout << "Socket binding failed.!" << std::endl;
    exit(1);
  }
  // Поставим сервер на прием данных 
  connection_status = listen(socket_file_descriptor, 5);
  if(connection_status == -1) {
    std::cout << "Socket is unable to listen for new connections.!" << std::endl;
    exit(1);
  } else {
    std::cout << "Server is listening for new connection: " << std::endl;
  }
  length = sizeof(client);
  connection = accept(socket_file_descriptor,(struct sockaddr*)&client, &length);
  if(connection == -1)  {
    std::cout << "Server is unable to accept the data from client.!" << std::endl;
    exit(1);
  }
}

bool create_client_connection() {
  // Создадим сокет
  socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if(socket_file_descriptor == -1){
    std::cout << "Creation of Socket failed!" << std::endl;
      exit(1);
  }
  // Установим адрес сервера
  serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  // Зададим номер порта
  serveraddress.sin_port = htons(PORT);
  // Используем IPv4
  serveraddress.sin_family = AF_INET;
  // Установим соединение с сервером
  connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
  if(connection == -1){
    std::cout << "Connection with the server failed.!" << std::endl;
    exit(1);
  }
  return true;
}

std::string sendToServer(std::string msg) {
  bzero(message, sizeof(message));
  strcpy(message, msg.c_str());
  if ((strncmp(message, "end", 3)) == 0) {
    write(socket_file_descriptor, message, sizeof(message));
    std::cout << "Client Exit." << std::endl;
  }
  ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
  // Если передали >= 0  байт, значит пересылка прошла успешно
  if(bytes >= 0) {
    std::cout << "Data send to the server successfully.!" << std::endl;
  }
  bzero(message, sizeof(message));
  // Ждем ответа от сервера
  read(socket_file_descriptor, message, sizeof(message));
  return std::string(message);
}