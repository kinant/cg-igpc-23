/*
	CGSpectrum IGPC Cert T1
	Week 06 Challenge 01 - Find the greatest value in an array, no matter the size
	By: Kinan Turman. 2023
*/

#include <iostream>
#include <time.h>
#include <assert.h>

using std::cout;
using std::cin;
using std::endl;

template <typename T>
void PopulateArray(T A[], const int Size);

template <typename T>
void PrintArray(const T A[], const int Size);

template <typename T>
T GetMax(const T A[], const int Size);

double RandomDouble();

int main()
{
	srand((unsigned)time(0));

	// get random sizes for arrays
	int SizeSmall = (3 + rand() % 10);
	int SizeMedium = (25 + rand() % 50);
	int SizeLarge = (50 + rand() % 100);

	// create an array of doubles, populate it, print it and get the max value
	double* pArrayDouble = new double[SizeSmall];
	PopulateArray<double>(pArrayDouble, SizeSmall);
	PrintArray<double>(pArrayDouble, SizeSmall);

	cout << endl;
	cout << "Max Value of Above Array is: " << (double)GetMax(pArrayDouble, SizeSmall) << endl;
	cout << endl;

	delete[] pArrayDouble;
	pArrayDouble = nullptr;

	// create an array of floats, populate it, print it and get the max value
	float* pArrayFloat = new float[SizeMedium];
	PopulateArray<float>(pArrayFloat, SizeMedium);
	PrintArray<float>(pArrayFloat, SizeMedium);

	cout << endl;
	cout << "Max Value of Above Array is: " << (float)GetMax(pArrayFloat, SizeMedium) << endl;
	cout << endl;

	delete[] pArrayFloat;
	pArrayFloat = nullptr;

	// create an array of ints, populate it, print it and get the max value
	int* pArrayInt = new int[SizeLarge];
	PopulateArray<int>(pArrayInt, SizeLarge);
	PrintArray<int>(pArrayInt, SizeLarge);

	cout << endl;
	cout << "Max Value of Above Array is: " << (int)GetMax(pArrayInt, SizeLarge) << endl;
	cout << endl;

	delete[] pArrayInt;
	pArrayInt = nullptr;
}

/*
* Function - RandomDouble
*	Generates a random double
* 
* @return - the randomnly generated double
*/
double RandomDouble() 
{
	return (double)(1 + rand() % (1 + rand() % 200)) / (double)(1 + rand() % (1 + rand() % 10));
}

/*
* Function - Generic Function that populates an array with random values
*
* @param A - the Array to populate
* @param Size - the size of the array
*/
template<typename T>
void PopulateArray(T* A, const int Size)
{
	if (Size == 0)
	{
		return;
	}

	for (int i = 0; i < Size; i++)
	{
		T RandValue = RandomDouble();
		A[i] = RandValue;
	}
}

/*
* Function - Generic Function that prints an array to console
*
* @param A - the Array to print
* @param Size - the size of the array
*/
template<typename T>
void PrintArray(T* A, const int Size)
{
	cout << "======== PRINTING ARRAY ========" << endl;

	for (int i = 0; i < Size; i++)
	{
		if (i % 5 == 0) {
			cout << endl;
		}
		cout << A[i] << " ";

		if (A[i] < 10) {
			cout << "  ";
		}
		else if (A[i] < 100)
		{
			cout << " ";
		}
	}
	cout << endl;
	cout << endl;
	cout << "==============================" << endl;
}

/*
* Function - Generic Function that gets the max value of the elements in an array
*
* @param A - the Array to check
* @param Size - the size of the array
*
* @return - the max value in the array
*/
template<typename T>
T GetMax(T* A, int Size)
{
	assert(Size > 0);
	T MaxValue = A[0];

	for (int i = 0; i < Size; i++)
	{
		if (MaxValue < A[i])
		{
			MaxValue = A[i];
		}
	}

	return MaxValue;
}
