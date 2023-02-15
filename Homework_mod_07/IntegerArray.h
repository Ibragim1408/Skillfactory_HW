#pragma once

class IntegerArray {
public:
	IntegerArray() : _size(0), _headArr(nullptr) {};
	IntegerArray(const int& size);
	IntegerArray(IntegerArray& other);

	int& operator[](const int& index);

	~IntegerArray();
	void erase();
	void resize(const int& newSize);
	void reallocate(const int& newSize);

	void insertBefore(const int& value, const int& index);
	void remove(const int& index);

	void insertFirst(const int& value) { insertBefore(value, 0); };
	void insertLast(const int& value)  { insertBefore(value, _size); };
	int findElement(const int& value) const;

	int size() const { return _size; };
	void print() const;
private:
	int _size;
	int* _headArr;
};