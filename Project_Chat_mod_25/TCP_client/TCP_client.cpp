#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include "../src/helper.h"
#include "../src/connect.h"


int main() {
  Chat chat(ChatObject::kChatClient);
  chat.start();

  if (!create_client_connection()) {
    return 0;
  }
  while(chat.isWorking()) {
    auto input = chat.showStartMenu();
    if (input.second.empty()) continue;
    std::string str_message = PrepareMessage(chat, input);

    std::string response = sendToServer(str_message);
    if (response == "-1") {
      continue ;
    }
    HandleResponse(chat, input.first, response);

    while (chat.getCurrentUser()) {
      input = chat.showUserMenu();
      if (input.second.empty()) continue;
      std::string str_message = PrepareMessage(chat,input);

      std::string response = sendToServer(str_message);
      if (response == "-1") {
        continue ;
      }
      HandleResponse(chat, input.first, response);
    }
  }

  close(socket_file_descriptor);
  return 0;
}
