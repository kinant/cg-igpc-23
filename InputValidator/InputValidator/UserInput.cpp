#include "UserInput.h"

template<class T>
void InputValidator::GenericUserInput(T& input, std::string promptMessage)
{

	std::cout << promptMessage;

	while (!(std::cin >> input)) 
	{
		ClearCin();
		std::cout << "Invalid input. Try again: ";
	}
}

void InputValidator::UserInput()
{
	int n;
	GenericUserInput(n, "");
}
