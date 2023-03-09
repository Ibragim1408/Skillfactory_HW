#include "chat.h"
#include "iostream"
#include "string.h"

Chat::Chat() {
  data_count = 0;
}
void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
  // Ваш код
  data[data_count++] = AuthData(_login, sha1(_pass, pass_length));
}
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
  // Ваш код
  // Нужно вернуть true в случае успешного логина
  int i = 0;
  for (; i < data_count; i++) {
    AuthData& ad = data[i];
    if (!strcmp(ad.login, _login)) {
      break;
    }
  }
  if (i >= data_count) return false;

  uint* digest = sha1(_pass, pass_length);

  bool cmpHashes = !memcmp(
    data[i].pass_sha1_hash,
    digest,
    SHA1HASHLENGTHBYTES);
  delete[] digest;

  return cmpHashes;
}