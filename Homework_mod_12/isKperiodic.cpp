#include <iostream>
#include <string>

bool isKperiodic(const std::string& str, int K) {
  // проверяем корректность ввода К, K должно быть больше 0
  // и размер искходной строки должен быть кратен К
  if (K < 1 || str.size() % K != 0) return false;
  // теперь можно проверить кратность, проверяя встречается ли i-ый символ каждые К позиций 
  size_t periodic = str.size() / K;
  for (size_t i = 0; i < K; ++i) {
    for (size_t j = 1; j < periodic; ++j) {
      if (str[i] != str[i + j * K]) return false;
    }
  }
  return true;
}

int main() {
  std::string str = "foofoofoofoo";
  std::cout << str << ": ";
  for (int i = -1; i < 10; ++i) {
    std::cout << i << ": " << isKperiodic(str, i) << " ";
  }
  std::cout << std::endl;
  str = "foofoofoofo";
  std::cout << str << ": ";
  for (int i = -1; i < 10; ++i) {
    std::cout << i << ": " << isKperiodic(str, i) << " ";
  }
  std::cout << std::endl;
  str = "foobarfoobarfoobarfoobar";
  std::cout << str << ": ";
  for (int i = -1; i < 15; ++i) {
    std::cout << i << ": " << isKperiodic(str, i) << " ";
  }
  std::cout << std::endl;
  return 0;
}