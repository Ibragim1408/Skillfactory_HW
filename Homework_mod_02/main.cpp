#include <iostream>

#define printOp(x, y, op, res) cout << x << " "<< op << " " << y << " = " << res << endl

using namespace std;

int main() {
	char op;
	setlocale(LC_ALL, "Russian");

	cout << "������� �������� ��� q - ��� ������" << endl;
	cin >> op;
	while (op != 'q') {
		if (op == '!') {
			int x;
			cout << "������� ����� ����� ��� ������� ����������" << endl;
			cin >> x;
			int res = 1;
			for (int i = 1; i <= x; i++) {
				res *= i;
			}
			cout << x << "! = " << res << endl;
		}
		else {
			int x, y;
			cout << "������� 2 ����� �����" << endl;
			cin >> x >> y;
			switch (op) {
			case '+':
				printOp(x, y, op, x + y);
				break;
			case '-':
				printOp(x, y, op, x - y);
				break;
			case '*':
				printOp(x, y, op, x * y);
				break;
			case '/':
				if (y == 0) {
					cout << "����������� ����� ����, ������������ ��������!" << endl;
				}
				else {
					printOp(x, y, op, x / (double)y);
				}
				break;
			case '^': {
				int res = 1; // �������� � � ������� �, ���� ������� �������, �� ����� 1
				for (int i = 1; i <= y; i++) {
					res *= x;
				}
				printOp(x, y, op, res);
				break;
			}
			default:
				cout << "������ ������������ ��������" << endl;
				break;
			}
		}
		cout << "������� �������� ��� q - ��� ������" << endl;
		cin >> op;
	}
	return 0;
}