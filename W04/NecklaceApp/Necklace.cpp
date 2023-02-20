#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

bool IsNecklaceComplete(const vector<int>& sequence, const int number1, const int number2);
void GetNextNumberInSequence(vector<int>& sequence);
void PrintSequence(const vector<int>& sequence);

int main() 
{
	int number1;
	cout << "Please enter the first number: " << endl;
	cin >> number1;

	int number2;
	cout << "Please enter the second number: " << endl;
	cin >> number2;

	vector<int> sequence;
	sequence.push_back(number1);
	sequence.push_back(number2);
	GetNextNumberInSequence(sequence);

	while (!IsNecklaceComplete(sequence, number1, number2)) 
	{
		GetNextNumberInSequence(sequence);
	}

	PrintSequence(sequence);

	return(0);
}

bool IsNecklaceComplete(const vector<int>& sequence, const int number1, const int number2) 
{
	return (sequence[sequence.size() - 2] == number1 && sequence[sequence.size() - 1] == number2);
}

void GetNextNumberInSequence(vector<int>& sequence)
{
	if (sequence.size() < 2) 
	{
		cout << "Not enough numbers in sequence to continue. Exiting program...";
		exit(-1);
	}

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




