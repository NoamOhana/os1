#include <iostream>
#include <stdio.h>

using namespace std;

int b;

void foo() {
}

int main() {
	int a;
	void *ptr = (void *)&foo;
	cout << "local: " << (&a) << endl;
	cout << "global: " << (&b) << endl;
	cout << "function: " << (ptr) << endl;
	printf("printf main: %p\n", main);
	printf("printf function: %p\n", foo);
	cout << "function itself:" << (&main) << endl;
	void *ptr2 = new char[10];
	cout << "heap: " << ptr2 << endl;
	delete [] ptr2;
	return 0;
}
