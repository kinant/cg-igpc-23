#include <iostream>
#include <vector>
#include "UserInput.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

using UInput::UserInput;

bool IsNecklaceComplete(const vector<int>& sequence, const int number1, const int number2);
void GetNextNumberInSequence(vector<int>& sequence);
void PrintSequence(const vector<int>& sequence);

int main() 
{
	// Prompt user for both numbers
	int number1;
	UserInput::GetUserInputRange(number1, "Enter 1st number (1-9): ", 1, 9);

	int number2;
	UserInput::GetUserInputRange(number2, "Enter 2nd number (1-9): ", 1, 9);

	// Add both numbers to vector list
	vector<int> sequence;
	sequence.push_back(number1);
	sequence.push_back(number2);

	GetNextNumberInSequence(sequence);

	// Run the loop while the necklace is not complete
	while (!IsNecklaceComplete(sequence, number1, number2)) 
	{
		GetNextNumberInSequence(sequence);
	}

	PrintSequence(sequence);

	return(0);
}

bool IsNecklaceComplete(const vector<int>& sequence, const int number1, const int number2) 
{
	// Check that the last and second to last numbers are equal to number 2 and number 1 respectively 
	return (sequence[sequence.size() - 2] == number1 && sequence[sequence.size() - 1] == number2);
}

void GetNextNumberInSequence(vector<int>& sequence)
{
	// Make sure there are at least two numbers, so we can calculate the next one in the sequence
	if (sequence.size() < 2) 
	{
		cout << "Not enough numbers in sequence to continue. Exiting program...";
		exit(-1);
	}

	// The next number in the sequence is just the addition of the last two numbers in the list/vector
	int NextNumberInSequence = (sequence[sequence.size() - 2] + sequence[sequence.size() - 1]) % 10;
	sequence.push_back(NextNumberInSequence);
}

void PrintSequence(const vector<int>& sequence)
{
	"SOLUTION NECKLACE SEQUENCE: ";

	for (int i : sequence) 
	{
		cout << i  << " ";
	}

	cout << endl;
}




