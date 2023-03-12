#include <iostream>

void DoSomething1(int& number);
void DoSomething2(int &number);
void DoSomething3(int & number);
void DoSomething4(int& number);
int* DoSomething5();

using std::cout;
using std::endl;

int main() 
{
	int num = 5;
	DoSomething1(num);
	DoSomething2(num);
	DoSomething3(num);

	int* number2 = &num;
	int *number3 = &num;
	
	DoSomething1(*number2);
	DoSomething4(*number3);

	int* myIntArray = DoSomething5();
	delete[] myIntArray;
}

void DoSomething1(int& number) 
{
	cout << "Do something 1: " << number << endl;
}
void DoSomething2(int &number) 
{
	cout << "Do something 2: " << number << endl;
}
void DoSomething3(int & number) 
{
	cout << "Do Something 3: " << number << endl;
}

void DoSomething4(int& a) 
{
	int* ptrExample = &a;
	cout << "Do Something 4: " << *ptrExample << endl;
	cout << "Do Something 4: " << a << endl;
}

int* DoSomething5() {
	int* intArray = new int[5];

	for (int i = 0; i < 5; i++) 
	{
		intArray[i] = (i + 1) * 3;
	}

	return intArray;
}
