/*
	CGSpectrum IGPC Cert T1
	Week 04 Challenge 1 V2 - Program that solves the Necklace Problem without using vectors
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

void NecklaceProblem(int Number1, int Number2, const int& OriginalNum1, const int& OriginalNum2) 
{
	const int NextNumber = (Number1 + Number2) % 10;
	cout << NextNumber << " ";

	if (Number2 == OriginalNum1 && NextNumber == OriginalNum2) 
	{
		return;
	}
	else 
	{
		NecklaceProblem(Number2, NextNumber, OriginalNum1, OriginalNum2);
	}
}

int main()
{
	// Prompt user for both numbers
	int Number1;
	UserInput::GetUserInputRange(Number1, "Enter 1st number (1-9): ", 1, 9);

	int Number2;
	UserInput::GetUserInputRange(Number2, "Enter 2nd number (1-9): ", 1, 9);

	// Output the first two numbers and solve the problem (recursively)
	cout << Number1 << " " << Number2 << " ";

	NecklaceProblem(Number1, Number2, Number1, Number2);
}