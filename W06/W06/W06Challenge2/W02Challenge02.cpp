#include <iostream>
#include <time.h>

using std::cout;
using std::endl;

constexpr int kSize = 100;

int RandomInt();
void PrintArray(const int Array[]);

int main()
{
	srand((unsigned)time(0));

	// create and populate an array of 100 random digits
	int MyArray[kSize];

	// rather than having to remember the size of the array
	// we can: https://www.w3schools.com/cpp/cpp_arrays_size.asp
	for (int i = 0; i < sizeof(MyArray) / sizeof(int); i++)
	{
		MyArray[i] = RandomInt();
	}

	PrintArray(MyArray);
}

void PrintArray(const int A[])
{
	cout << "======== PRINTING ARRAY ========" << endl;

	for (int i = 0; i < kSize; i++)
	{
		if (i % 10 == 0) {
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

int RandomInt()
{
	return (1 + rand() % (1 + rand() % 200));
}