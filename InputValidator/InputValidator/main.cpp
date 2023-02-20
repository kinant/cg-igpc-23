#include "UserInput.h"
#include<string>

using std::string;
using UInput::UserInput;

int main() 
{
	int testInt;
	double testDouble;
	char testChar;
	string testString;

	UserInput::GenericUserInput(testInt, "Please input a number: ");
	std::cout << "Test int: " << testInt << std::endl;

	UserInput::GenericUserInput(testInt, "Please input a number: ", 1, 100);
	std::cout << "Test int (1-100): " << testInt << std::endl;

	return 0;
}