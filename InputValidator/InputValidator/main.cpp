#include "inputValidator.h"
#include<string>

using std::string;

int main() 
{
	int testInt;
	double testDouble;
	char testChar;
	string testString;

	InputValidator::GetUserInput(testInt);
	std::cout << "Test int: " << testInt << std::endl;

	return 0;
}