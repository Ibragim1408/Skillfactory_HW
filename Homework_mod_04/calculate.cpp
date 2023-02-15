#include "calculate.h"

using namespace std;


#define printOp(x, y, op, res) cout << x << " "<< op << " " << y << " = " << res << endl

void printSum(const int& a, const int& b) {
	printOp(a, b, '+', a + b);
}

void printDif(const int& a, const int& b) {
	printOp(a, b, '-', a - b);
}
void printProduct(const int& a, const int& b) {
	printOp(a, b, '*', a * b);
}
void printDivide(const int& a, const int& b) {
	printOp(a, b, '/', a / (float)b);
}

void printPower(const int& a, const int& b) {
	printOp(a, b, '^', calcPower(a, b));
}

void printFactorial(const int& a) {
	cout << a << "! = " << calcFactorial(a) << endl;
}

int calcPower(const int& a, const int& b) {
	if (b == 0)
		return 1;
	else if (b == 1)
		return a;
	else
		return a * calcPower(a, b - 1);
}

int calcFactorial(const int& a) {
	if (a <= 1)
		return a;
	else
		return a * calcFactorial(a - 1);
}
