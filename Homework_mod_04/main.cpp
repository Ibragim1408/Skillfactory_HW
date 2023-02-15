#include "calculate.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	while (true) {
		char op;
		cout << "������� �������� ��� q - ��� ������" << endl;
		cin >> op;
		if (op == 'q')
			break;
		if (op == '!') {
			int x;
			cout << "������� ����� ����� ��� ������� ����������" << endl;
			cin >> x;
			printFactorial(x);
		}
		else {
			int x, y;
			cout << "������� 2 ����� �����" << endl;
			cin >> x >> y;
			switch (op) {
			case '+':
				printSum(x, y);
				break;
			case '-':
				printDif(x, y);
				break;
			case '*':
				printProduct(x, y);
				break;
			case '/':
				if (y == 0) {
					cout << "����������� ����� ����, ����������� ��������!" << endl;
				}
				else {
					printDivide(x, y);
				}
				break;
			case '^': {
				printPower(x, y);
				break;
			}
			default:
				cout << "������ ������������ ��������" << endl;
				break;
			}
		}
	}
	return 0;
}