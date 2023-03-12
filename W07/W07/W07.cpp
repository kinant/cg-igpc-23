#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void PrintNumbers(const int& numA, const int& numB);
void PrintNumbersByPointer(int* numA, int* numB);
void Swap(int* ptrA, int* ptrB);

int main() 
{
	int numA;
	int numB;

	cout << "Input First Number: ";
	cin >> numA;

	cout << "Input Second Number: ";
	cin >> numB;

	cout << endl;

	PrintNumbers(numA, numB);

	Swap(&numA, &numB);

	cout << endl;

	PrintNumbers(numA, numB);

	PrintNumbersByPointer(&numA, &numB);
}

void PrintNumbers(const int& numA, const int& numB) 
{
	cout << "First number is: " << numA << endl;
	cout << "Second number is: " << numB << endl;
}

void PrintNumbersByPointer(int* numA, int* numB) 
{
	cout << "First number is: " << *numA << endl;
	cout << "Second number is: " << *numB << endl;
}

void Swap(int* ptrA, int* ptrB) 
{
	int* tempPtr = ptrA;
	ptrA = ptrB;
	ptrB = tempPtr;
}