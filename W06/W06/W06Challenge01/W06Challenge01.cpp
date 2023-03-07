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
	srand((unsigned)time(0));

	int sizeSmall = (3 + rand() % 10);
	int sizeMedium = (25 + rand() % 50);
	int sizeLarge = (50 + rand() % 100);

	double* ptArrayDouble = new double[sizeSmall];
	PopulateArray<double>(ptArrayDouble, sizeSmall);
	PrintArray<double>(ptArrayDouble, sizeSmall);

	cout << endl;
	cout << "Max Value of Above Array is: " << (double)GetMax(ptArrayDouble, sizeSmall) << endl;
	cout << endl;

	delete[] ptArrayDouble;
	ptArrayDouble = nullptr;

	float* ptArrayFloat = new float[sizeMedium];
	PopulateArray<float>(ptArrayFloat, sizeMedium);
	PrintArray<float>(ptArrayFloat, sizeMedium);

	cout << endl;
	cout << "Max Value of Above Array is: " << (float)GetMax(ptArrayFloat, sizeMedium) << endl;
	cout << endl;

	delete[] ptArrayFloat;
	ptArrayFloat = nullptr;

	int* ptArrayInt = new int[sizeLarge];
	PopulateArray<int>(ptArrayInt, sizeLarge);
	PrintArray<int>(ptArrayInt, sizeLarge);

	cout << endl;
	cout << "Max Value of Above Array is: " << (int)GetMax(ptArrayInt, sizeLarge) << endl;
	cout << endl;

	delete[] ptArrayInt;
	ptArrayInt = nullptr;
}

template<typename T>
void PopulateArray(T* a, const int size)
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
void PrintArray(T* a, const int size)
{
	cout << "======== PRINTING ARRAY ========" << endl;

	for (int i = 0; i < size; i++)
	{
		if (i % 5 == 0) {
			cout << endl;
		}
		cout << a[i] << " ";

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
T GetMax(T* a, int size)
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
