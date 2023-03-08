/*
	CGSpectrum IGPC Cert T1
	Week 06 Challenge 02 - Find the N greatest values in an array of numbers.
	It is basically a combination of this example: https://www.w3resource.com/cpp-exercises/array/cpp-array-exercise-2.php,
	with this example: https://www.w3resource.com/cpp-exercises/array/cpp-array-exercise-4.php, without using sorting.

	By: Kinan Turman. 2023
*/
#include <iostream>
#include <time.h>
#include <assert.h>

using std::cout;
using std::endl;

constexpr int kSize = 300;
constexpr int kNValue = 25;

int RandomInt();
void PrintArray(const int MyArray[], const int Size);
void LargestKElements(const int MyArray[]);

int main()
{
	srand((unsigned)time(0));

	// create and populate an array of kSize random digits
	int MyArray[kSize];

	for (int i = 0; i < kSize; i++)
	{
		MyArray[i] = RandomInt();
	}

	PrintArray(MyArray, kSize);

	LargestKElements(MyArray);
}

/*
* Function - PrintArray
*	Prints an array to console
*
* @param MyArray[] - array of integers to print to console
* @param Size - the size of the array
*/
void PrintArray(const int MyArray[], const int Size)
{
	cout << "======== PRINTING ARRAY ========" << endl;

	for (int i = 0; i < Size; i++)
	{
		if (i % 10 == 0) {
			cout << endl;
		}
		cout << MyArray[i] << " ";

		if (MyArray[i] < 10) {
			cout << "  ";
		}
		else if (MyArray[i] < 100)
		{
			cout << " ";
		}
	}
	cout << endl;
	cout << endl;
	cout << "==============================" << endl;
}

/*
* Function - RandomInt
*	Generates a random int from 1 - 200
*
* @return - the randomnly generated int
*/
int RandomInt()
{
	return (1 + rand() % (1 + rand() % 200));
}

/*
* Function - RandomInt
*	Finds the largest N Elements inside an array, given by kNValue
*	Q&A: I tried using a dynamic array (declared and deleted inside the function), but it kept giving me errors.
*
* @param MyArray - the Array to get the Nth Largest elements from
*
* @return - the randomnly generated int
*/
void LargestKElements(const int MyArray[])
{
	// make sure we are not trying to get the largest N numbers where N > the size of the array
	assert(kSize >= kNValue);

	// declare and initialize the array to store all the largest N numbers
	int* Largest = new int[kNValue]{ 0 };

	// iterate over each element of the array
	for (int i = 0; i < kSize; i++)
	{
		// iterate over each of the current Largest numbers
		for (int j = 0; j < kNValue; j++) {

			// if the value of the array at i is grater than the value if Largest at j
			// then we have a new largest number
			if (MyArray[i] > Largest[j])
			{
				// iterate over each element in largest
				// making the last Gth Largest value take the value of the Gth-1 
				// (basically bump them down, starting from the last value)
				// ERROR: can produce similar error by changing (kNValue-1) to (kNValue)
				for (int g = (kNValue - 1); g > j; g--)
				{
					// ERROR: The following line would be underlined:
					Largest[g] = Largest[g - 1];
				}
				// set the "new" largest value in the appropiate position
				Largest[j] = MyArray[i];
				
				// done assigning new values
				break;
			}
		}
	}

	cout << "THE LARGEST " << kNValue << " ELEMENTS IN THE ARRAY: " << endl;
	PrintArray(Largest, kNValue);

	delete[] Largest; // <-- Retrying after ABORT would show a tiny little (x) here. 
	Largest = nullptr;
}