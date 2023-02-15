#include "UserInput.h"
#include<string>

using std::string;

int main() 
{
	int testInt;
	double testDouble;
	char testChar;
	string testString;

	InputValidator::GenericUserInput(testInt, "Please input a number: ");
	std::cout << "Test int: " << testInt << std::endl;

	return 0;
}