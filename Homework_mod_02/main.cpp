#include <iostream>

#define printOp(x, y, op, res) cout << x << " "<< op << " " << y << " = " << res << endl

using namespace std;

int main() {
	char op;
	setlocale(LC_ALL, "Russian");

	cout << "¬ведите операцию или q - дл€ выхода" << endl;
	cin >> op;
	while (op != 'q') {
		if (op == '!') {
			int x;
			cout << "¬ведите целое число дл€ расчета факториала" << endl;
			cin >> x;
			int res = 1;
			for (int i = 1; i <= x; i++) {
				res *= i;
			}
			cout << x << "! = " << res << endl;
		}
		else {
			int x, y;
			cout << "¬ведите 2 целых числа" << endl;
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
					cout << "«наменатель равен нулю, недопустима€ операци€!" << endl;
				}
				else {
					printOp(x, y, op, x / (double)y);
				}
				break;
			case '^': {
				int res = 1; // возводим х в степень у, ксли степень нулева€, то будет 1
				for (int i = 1; i <= y; i++) {
					res *= x;
				}
				printOp(x, y, op, res);
				break;
			}
			default:
				cout << "¬веден некорректный оператор" << endl;
				break;
			}
		}
		cout << "¬ведите операцию или q - дл€ выхода" << endl;
		cin >> op;
	}
	return 0;
}