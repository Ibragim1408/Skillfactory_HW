#include "chat.h"


int main() {
  Chat chat;
  chat.start();

  while (chat.isWorking()) {
    
    chat.showStartMenu();
    
    while (chat.getCurrentUser()) {
      chat.showUserMenu();
    }
  }

  return 0;
}
