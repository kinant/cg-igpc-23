/*
	CGSpectrum IGPC Cert T1
	Week 04 Challenge 2 V2 - Program that solves the Necklace Problem without using vectors
	By: Kinan Turman. 2023

	Used the following resource to calculate a random number between a range:
	https://www.w3schools.blog/random-in-range-c
*/

#include <iostream>
#include "UserInput.h"

using std::cout;
using std::cin;
using std::endl;

using UInput::UserInput;

// Q&A: How to properly name constants
constexpr int MaxInt = 9;
constexpr int MinInt = 1;

void NecklaceProblem(int Number1, int Number2, const int& OriginalNum1, const int& OriginalNum2);

int main()
{
	// Prompt user for both numbers
	int Number1;
	UserInput::GetUserInputRange(Number1, "Enter 1st number (1-9): ", MinInt, MaxInt);

	int Number2;
	UserInput::GetUserInputRange(Number2, "Enter 2nd number (1-9): ", MinInt, MaxInt);

	// Output the first two numbers and solve the problem (recursively)
	cout << Number1 << " " << Number2 << " ";

	NecklaceProblem(Number1, Number2, Number1, Number2);
}

/*
* Function - Necklace Problem
* Function that recursively solves the necklace problem.
* Adds two numbers in a sequence, to get the next value (just the tenths digit)
* Stops once the sequence contains the original first two numbers in order.
*
* @param Number1 - The first number that will be used to calculate the next number in the sequence
* @param Number2 - The second number that will be used to calculate the next number in the sequence
* @param OriginalNum1 - The original first number
* @param OriginalNum2 - The original second number
*/
void NecklaceProblem(int Number1, int Number2, const int& OriginalNum1, const int& OriginalNum2)
{
	// get the next number in the sequence and output it
	const int NextNumber = (Number1 + Number2) % 10;
	cout << NextNumber << " ";

	// check if the sequence is complete (ie. necklace complete)
	if (Number2 == OriginalNum1 && NextNumber == OriginalNum2)
	{
		return;
	}
	else
	{
		// call funcion recursively until the sequence/necklace is complete
		NecklaceProblem(Number2, NextNumber, OriginalNum1, OriginalNum2);
	}
}