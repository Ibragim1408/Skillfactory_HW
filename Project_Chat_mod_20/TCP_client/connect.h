#pragma once
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include<iostream>

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777 

struct sockaddr_in serveraddress, client;
socklen_t length;
int socket_file_descriptor, connection, bind_status, connection_status;
char message[MESSAGE_LENGTH];

void create_connection();

void create_connection() {
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