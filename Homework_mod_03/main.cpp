#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "������� 1 ��� ����������, 2 ��� ������������ ��� ������ ��� ������" << endl;
	int flag;
	cin >> flag;
	char upperChar[26], lowerChar[26];
	for (int i = 0; i < 26; i++) {
		upperChar[i] = 'A' + i;
		lowerChar[i] = 'a' + i;
	}
	while (flag == 1 || flag == 2) {
		// ������� ������
		cout << "������� ����� ������" << endl;
		int lenght, dif;
		cin >> lenght;
		cout << "������� ������:" << endl;
		char* str = new char[lenght];
		for (int i = 0; i < lenght; i++) {
			cin >> str[i];
		}
		cout << "������� �������� ������:" << endl;
		cin >> dif;
		dif %= 26; // ��������� ����� ��� ������ ������ 26
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
		cout << "������� 1 ��� ���������� ��� 2 ��� ������������" << endl;
		cin >> flag;
		delete[] str;
	}
	return 0;
}