#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите 1 дл€ шифровани€, 2 дл€ дешифровани€ или прочее дл€ выхода" << endl;
	int flag;
	cin >> flag;
	char upperChar[26], lowerChar[26];
	for (int i = 0; i < 26; i++) {
		upperChar[i] = 'A' + i;
		lowerChar[i] = 'a' + i;
	}
	while (flag == 1 || flag == 2) {
		// входные данные
		cout << "¬ведите длину строки" << endl;
		int lenght, dif;
		cin >> lenght;
		cout << "¬ведите строку:" << endl;
		char* str = new char[lenght];
		for (int i = 0; i < lenght; i++) {
			cin >> str[i];
		}
		cout << "¬ведите величину сдвига:" << endl;
		cin >> dif;
		dif %= 26; // нормируем сдвиг дл€ сдвига больше 26
		//
		for (int i = 0; i < lenght; i++) {
			if (str[i] >= 'A' && str[i] <= 'Z') {
				int newIndex = str[i] - 'A';
				if (flag == 1) {
					newIndex = (newIndex + dif) % 26;
				}
				else {
					newIndex = newIndex - dif < 0 ? 26 + newIndex - dif : newIndex - dif;
				}
				str[i] = upperChar[newIndex];
			} 
			else if (str[i] >= 'a' && str[i] <= 'z') {
				int newIndex = str[i] - 'a';
				if (flag == 1) {
					newIndex = (newIndex + dif) % 26;
				}
				else {
					newIndex = newIndex - dif < 0 ? 26 + newIndex - dif : newIndex - dif;
				}
				str[i] = lowerChar[newIndex];
			}
		}
		
		for (int i = 0; i < lenght; i++) {
			cout << str[i];
		}
		cout << endl;
		cout << "¬ведите 1 дл€ шифровани€ или 2 дл€ дешифровани€" << endl;
		cin >> flag;
		delete[] str;
	}
	return 0;
}