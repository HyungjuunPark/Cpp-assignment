#include <iostream>
using namespace std;

class DynamicArray {
private:
	int* data;
	int size;

public:
	DynamicArray(int n) : size(n) {
		data = new int[n];
		for (int i = 0; i < n; i++) data[i] = i;
	}

	DynamicArray(const DynamicArray& copy) : size(copy.size) {
		data = new int[copy.size];
		for (int i = 0; i < copy.size; i++) data[i] = i;
	}

	void Set(int idx, int val) {
		if (idx >= 0 && idx < size)data[idx] = val;
	}
	
	void Print() {
		for (int i = 0; i < size; i++)cout << data[i] << " ";
		cout << '\n';
	}

	~DynamicArray() {
		delete[] data;
	}
};

int main() {
	DynamicArray arr1(5);
	DynamicArray arr2 = arr1;
	arr2.Set(0, 100);

	cout << "arr1: ";
	arr1.Print();
	cout << "arr2: ";
	arr2.Print();

	return 0;

}

