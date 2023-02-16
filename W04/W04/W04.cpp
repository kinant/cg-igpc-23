#include <iostream>
#include <time.h>
#include <assert.h>

using std::cout;
using std::cin;
using std::endl;

template <typename T> 
void PopulateArray(T a[], int size);

template <typename T>
void PrintArray(T a[], int size);

template <typename T>
T GetMax(T a[], int size);

double randomDouble()
{
	return (double)(1 + rand() % (1 + rand() % 200)) / (double)(1 + rand() % (1 + rand() % 10));
}

int main() 
{
	srand(time(0));

	constexpr int sizeSmall = 10;
	constexpr int sizeMedium = 50;
	constexpr int sizeLarge = 100;

	double arrayDouble[sizeSmall];
	PopulateArray(arrayDouble, sizeSmall);
	PrintArray(arrayDouble, sizeSmall);

	cout << endl;
	cout << "Max Value of Above Array is: " << (double)GetMax(arrayDouble, sizeSmall) << endl;
	cout << endl;

	float arrayFloat[sizeMedium];
	PopulateArray(arrayFloat, sizeMedium);
	PrintArray(arrayFloat, sizeMedium);

	cout << endl;
	cout << "Max Value of Above Array is: " << (float)GetMax(arrayFloat, sizeMedium) << endl;
	cout << endl;

	int arrayInt[sizeLarge];
	PopulateArray(arrayInt, sizeLarge);
	PrintArray(arrayInt, sizeLarge);

	cout << endl;
	cout << "Max Value of Above Array is: " << (int)GetMax(arrayInt, sizeMedium) << endl;
	cout << endl;
}

template<typename T>
void PopulateArray(T a[], const int size)
{
	if (size == 0) 
	{
		return;
	}

	for (int i = 0; i < size; i++) 
	{
		T randValue = randomDouble();
		a[i] = randValue;
	}
}

template<typename T>
void PrintArray(T a[], const int size)
{
	cout << "======== PRINTING ARRAY ========" << endl;

	for (int i = 0; i < size; i++) 
	{
		if (i % 5 == 0) {
			cout << endl;
		}
		cout << a[i] <<" ";

		if (a[i] < 10) {
			cout << "  ";
		}
		else if (a[i] < 100) 
		{
			cout << " ";
		}
	}
	cout << endl;
	cout << endl;
	cout << "==============================" << endl;
}

template<typename T>
T GetMax(T a[], int size)
{
	assert(size > 0);
	T maxValue = a[0];

	for (int i = 0; i < size; i++)
	{
		if (maxValue < a[i]) 
		{
			maxValue = a[i];
		}
	}

	return maxValue;
}
