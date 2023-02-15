#include "calculate.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	while (true) {
		char op;
		cout << "¬ведите операцию или q - дл€ выхода" << endl;
		cin >> op;
		if (op == 'q')
			break;
		if (op == '!') {
			int x;
			cout << "¬ведите целое число дл€ расчета факториала" << endl;
			cin >> x;
			printFactorial(x);
		}
		else {
			int x, y;
			cout << "¬ведите 2 целых числа" << endl;
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
					cout << "«наменатель равен нулю, недопустима§ операци€!" << endl;
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
				cout << "¬веден некорректный оператор" << endl;
				break;
			}
		}
	}
	return 0;
}