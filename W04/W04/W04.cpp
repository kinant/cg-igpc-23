/*
	CGSpectrum IGPC Cert T1
	Week 04 Challenge 4 - Program that calculates a number cubed of
	a user inputed number.
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

template <typename T> T Cubed(const T& Number);

int main() 
{
	// works with integers
	int IntegerNumber;
	UserInput::GetUserInput(IntegerNumber, "Please input integer: ");
	cout << "Number cubed is: " << Cubed(IntegerNumber);
	cout << endl;

	// works with floats
	float FloatNumber;
	UserInput::GetUserInput(FloatNumber, "Please input float: ");
	cout << "Number (float) cubed is: " << Cubed(FloatNumber);
	cout << endl;

	// works with doubles
	double DoubleNumber;
	UserInput::GetUserInput(DoubleNumber, "Please input double: ");
	cout << "Number (float) cubed is: " << Cubed(DoubleNumber);
	cout << endl;
}

/*
* Function - Cubed
* Template function that uses a generic type to calculate the value of a number cubed.
* Uses a template function so that it can work with any number data type
* @param Number - Reference to the number to be cubed. 
*/
template <typename T> T Cubed(const T& Number)
{
	return Number * Number * Number;
}
