#include "UserInput.h"
#include <iostream>

using std::cin;
using std::cout;
using std::string;

using UInput::UserInput;

int main() 
{
	// works for int
	int IntegerA;
	UserInput::GetUserInput(IntegerA, "Input an integer: ");
	cout << IntegerA << endl;

	// works for float
	float FloatA;
	UserInput::GetUserInput(FloatA, "Input a Float: ");
	cout << FloatA << endl;

	// works for char
	char CharA;
	UserInput::GetUserInput(CharA, "Input a char: ");
	cout << CharA << endl;

	// works for string
	string StringA;
	UserInput::GetUserInput(StringA, "Input a String: ");
	cout << StringA << endl;
}