#include "IntegerArray.h"
#include <iostream>

using std::cout;

int main()
{
	// проверка работоспособности массива - все функции работаю корректно и не выбрасывают исключение;
	IntegerArray arr1;	
	arr1.print();
	cout << arr1.findElement(3) << '\n';
	arr1.insertFirst(1);
	arr1.insertFirst(2);
	arr1.insertFirst(3);
	cout << arr1.findElement(3) << '\n';
	arr1.print();
	int oldSize = arr1.size();
	cout << oldSize << '\n';
	arr1.resize(10);
	for (int i = oldSize; i < arr1.size(); i++) {
		arr1[i] = i * 2 - 2;
	}
	cout << arr1.findElement(6) << '\n';
	arr1.print();
	arr1.resize(5);
	arr1.print();
	arr1.insertBefore(-6, 3);
	arr1.print();
	arr1.remove(4);
	arr1.print();
	arr1.insertLast(100);
	arr1.print();
	//
	cout << "Check extreme situation for insert" << '\n';
	arr1.insertBefore(19, 0);
	arr1.print();
	arr1.insertBefore(-17, arr1.size());
	arr1.print();
	cout << "Check extreme situation for remove" << '\n';
	arr1.remove(0);
	arr1.print();
	arr1.remove(arr1.size()-1);
	arr1.print();

	cout << "End of tests!" << '\n';
	try	{
		cout << arr1[-1] << '\n';
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
	try {
		cout << arr1[20] << '\n';
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
	try {
		arr1.resize(-2);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
	try {
		arr1.reallocate(-2);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
	try {
		arr1.remove(-2);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
	try {
		arr1.remove(17);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << '\n';
	}

	try {
		IntegerArray arr2(-5);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
	try {
		IntegerArray arr2(5);
		arr2.insertBefore(18, -2);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << '\n';
	}
	try {
		IntegerArray arr2(5);
		arr2.insertBefore(18, 8);
	}

	catch (const std::exception& ex) {
		std::cout << ex.what() << '\n';
	}

  std::cout << "the end\n";
  return 0;
}