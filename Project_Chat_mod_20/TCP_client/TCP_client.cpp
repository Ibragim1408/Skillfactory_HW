#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include "helper.h"
#include "connect.h"


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

  close(socket_file_descriptor);
  return 0;
}
