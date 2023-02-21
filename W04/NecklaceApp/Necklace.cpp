/*
	CGSpectrum IGPC Cert T1
	Week 04 Challenge 1 - Program that solves The Necklace Problem
	By: Kinan Turman. 2023

	Used the following resource to calculate a random number between a range:
	https://www.w3schools.blog/random-in-range-c
*/

#include <iostream>
#include <vector>
#include "UserInput.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

using UInput::UserInput;

bool IsNecklaceComplete(const vector<int>& Sequence, const int Number1, const int Number2);
void GetNextNumberInSequence(vector<int>& Sequence);
void PrintSequence(const vector<int>& Sequence);

int main() 
{
	// Prompt user for both numbers
	int Number1;
	UserInput::GetUserInputRange(Number1, "Enter 1st number (1-9): ", 1, 9);

	int Number2;
	UserInput::GetUserInputRange(Number2, "Enter 2nd number (1-9): ", 1, 9);

	// Add both numbers to vector list
	vector<int> Sequence;
	Sequence.push_back(Number1);
	Sequence.push_back(Number2);

	GetNextNumberInSequence(Sequence);

	// Run the loop while the necklace is not complete
	while (!IsNecklaceComplete(Sequence, Number1, Number2)) 
	{
		GetNextNumberInSequence(Sequence);
	}

	PrintSequence(Sequence);

	return(0);
}

/*
* Function -  IsNecklaceComplete
* Checks if the necklace problem is solved.
* @param Sequence - the list or vector representing the sequence of numbers
* @param Number1 - the first number of the sequence
* @param Number2 - the second number of the sequence
* @return - true if the Necklace is complete, false otherwise
*/

bool IsNecklaceComplete(const vector<int>& Sequence, const int Number1, const int Number2) 
{
	// Check that the last and second to last numbers are equal to number 2 and number 1 respectively 
	return (Sequence[Sequence.size() - 2] == Number1 && Sequence[Sequence.size() - 1] == Number2);
}

/*
* Function - GetNextNumberInSequence
* Gets the next number in the sequence and stores it in the list/vector
* @param Sequence - the list or vector representing the sequence of numbers
*/
void GetNextNumberInSequence(vector<int>& Sequence)
{
	// Make sure there are at least two numbers, so we can calculate the next one in the sequence
	if (Sequence.size() < 2) 
	{
		cout << "Not enough numbers in sequence to continue. Exiting program...";
		exit(-1);
	}

	// The next number in the sequence is just the addition of the last two numbers in the list/vector
	int NextNumberInSequence = (Sequence[Sequence.size() - 2] + Sequence[Sequence.size() - 1]) % 10;
	Sequence.push_back(NextNumberInSequence);
}

/*
* Function - PrintSequence
* Prints the necklace sequence to console
* @param Sequence - the list or vector representing the sequence of numbers
*/
void PrintSequence(const vector<int>& Sequence)
{
	cout << "SOLUTION NECKLACE SEQUENCE: " << endl;

	for (int i : Sequence) 
	{
		cout << i  << " ";
	}

	cout << endl;
}




