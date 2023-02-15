#include "IntegerArray.h"
#include <iostream>
#include "MyException.h"

IntegerArray::IntegerArray(const int& size) {
	if (size < 0) {
		throw BadLenght("bad_length for constructor");
	}
	else {
		_size = size;
		_headArr = size == 0 ? nullptr : new int[_size];
	}
}

IntegerArray::IntegerArray(IntegerArray& other) {
	_size = other._size;
	if (_size != 0) {
		_headArr = new int[_size];
		for (int i = 0; i < _size; i++) {
			_headArr[i] = other[i];
		}
	}
	else {
		_headArr = nullptr;
	}
}

int& IntegerArray::operator[](const int& index)
{
	if (index < 0 || index >= _size) {
		throw BadRange("bad_range for operator[]");
	}
	return _headArr[index];
}

void IntegerArray::erase() {
	if (_size != 0) {
		delete[] _headArr;
	}
	_size = 0;
	_headArr = nullptr;
}

void IntegerArray::resize(const int& newSize) {
	if (newSize < 0) {
		throw BadLenght("bad_length for resize");
	}
	else if (newSize == _size) 
		return;
	else if (newSize == 0) {
		erase();
	}
	else {
		int* newData = new int[newSize];
		int arrToCopy = newSize < _size ? newSize : _size;
		for (int i = 0; i < arrToCopy; i++) {
			newData[i] = _headArr[i];
		}
		delete[] _headArr;

		_size = newSize;
		_headArr = newData;
	}
}

void IntegerArray::reallocate(const int& newSize) {
	if (newSize < 0) {
		throw BadLenght("bad_length for reallocate");
	}
	else {
		erase();
		_size = newSize;
		_headArr = newSize == 0 ? nullptr : new int[_size];
	}
}

void IntegerArray::insertBefore(const int& value, const int& index) {
	if (index < 0 || index > _size)
		throw BadLenght("bad_length for insert");
	
	int* newData = new int[_size + 1];
	for (int i = 0; i < index; i++) {
		newData[i] = _headArr[i];
	}
	newData[index] = value;
	for (int i = index+1; i < _size+1; i++) {
		newData[i] = _headArr[i-1];
	}
	delete[] _headArr;
	_size++;
	_headArr = newData;
}

void IntegerArray::remove(const int& index) {
	if (index < 0 || index >= _size)
		throw BadLenght("bad_length for remove");
	int* newData = new int[_size - 1];
	for (int i = 0; i < index; i++) {
		newData[i] = _headArr[i];
	}
	for (int i = index; i < _size - 1; i++) {
		newData[i] = _headArr[i + 1];
	}

	delete[] _headArr;
	_size--;
	_headArr = newData;
}


int IntegerArray::findElement(const int& value) const {
	for (int i = 0; i < _size; i++) {
		if (_headArr[i] == value) {
			return i;
		}
	}
	return -1;
}

void IntegerArray::print() const {
	if (_size == 0) std::cout << "Array is Empty";
	else {
		for (int i = 0; i < _size; i++) {
			std::cout << _headArr[i] << " ";
		}
	}
	std::cout << '\n';
}

IntegerArray::~IntegerArray() {
	if (_size != 0)
		delete[] _headArr;
}
