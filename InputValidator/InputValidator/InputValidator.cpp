#include "inputValidator.h"

void InputValidator::GetUserInput(int& input)
{
	//std::cout << "Please input a number: ";
	GenericUserInput<int>(input);
}

template<class T>
void InputValidator::GenericUserInput(T& input)
{
	std::cin >> input;
}
