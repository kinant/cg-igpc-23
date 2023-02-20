// https://www.w3schools.blog/random-in-range-c

#include <iostream>
#include <stdlib.h>
#include "UserInput.h"

using std::cout;
using std::cin;
using std::endl;

using UInput::UserInput;

/*
* This function recursively calculates the number of iterations to randomnly pick a selected given number.
*
*@param MinRange - the minimuim range for the number
*@param MaxRange - the maximum range for the number
*@param SelectedNumber - the number selected by the user
*
@return - eventually returns the counter or number of iterations required to randomnly pick the selected number
*/

int RandomUntilSelectedNumber_Recursively(int MinRange, int MaxRange, int SelectedNumber)
{
	// Get a random number in the range
	int RandNum = MinRange + (rand() % (MaxRange - MinRange + 1));

	
	if (RandNum == SelectedNumber) 
	{
		// If the number is equal to the selected number, we return one
		return 1;
	}
	else 
	{
		// Otherwise we return 1 plus the function called recursively. (Works like keeping a counter)
		return 1 + RandomUntilSelectedNumber_Recursively(MinRange, MaxRange, SelectedNumber);
	}
}

/*
* This function non-recursively calculates the number of iterations to randomnly pick a selected given number.
* Uses a loop instead. 
*
*@param MinRange - the minimuim range for the number
*@param MaxRange - the maximum range for the number
*@param SelectedNumber - the number selected by the user
*
@return - eventually returns the counter or number of iterations required to randomnly pick the selected number
*/
int RandomUntilSelectedNumber_NonRecursively(int MinRange, int MaxRange, int SelectedNumber)
{
	// We start the counter at 1, on the chance that the first random generated int is the correct guess
	int Count = 1;

	// Loop while the random number in range is not the selected number
	while ((MinRange + (rand() % (MaxRange - MinRange + 1)) != SelectedNumber))
	{
		Count++;
	}

	return Count;
}

int main()
{
	int MinRange = 1;
	int MaxRange = 100;
	int SelectedNumber = 0;

	// Prompt user of input in the range
	UserInput::GetUserInputRange(SelectedNumber, "Enter number between 1 and 100: ", MinRange, MaxRange);

	// NOTE: This if statement becomes irrelevant after the previous function
	if (SelectedNumber >= 1 && SelectedNumber <= 100)
	{
		srand((unsigned)time(0));

		int Count = RandomUntilSelectedNumber_Recursively(MinRange, MaxRange, SelectedNumber);

		cout << "It took " << Count << " iterations to recursive function to randomly pick selected number " << SelectedNumber << endl;

		Count = RandomUntilSelectedNumber_NonRecursively(MinRange, MaxRange, SelectedNumber);

		cout << "It took " << Count << " iterations to non recursive function to randomly pick selected number " << SelectedNumber << endl;

	}

	system("PAUSE");
}