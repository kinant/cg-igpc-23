#include <iostream>
#include <string>
#include<limits>

#ifndef USER_INPUT_H
#define USER_INPUT_H

static const std::string ERROR_MESSAGE_GENERAL = "Invalid input. Try again:";

class InputValidator
{
public:
	

	template<class T> static void GenericUserInput(T& input, std::string promptMessage);
	
	template<class T> static void GenericUserInput(T& input, std::string promptMessage, 
		const int& min, const int& max);

private:

	static void ClearCin() 
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};

template<class T>
void InputValidator::GenericUserInput(T& input, std::string promptMessage)
{
	std::cout << promptMessage;

	while (!(std::cin >> input))
	{
		ClearCin();
		std::cout << ERROR_MESSAGE_GENERAL;
	}
}

template<class T>
inline void InputValidator::GenericUserInput(T& input, std::string promptMessage, const int& min, const int& max)
{
	std::cout << promptMessage;

	while (!(std::cin >> input) || (input < min || input > max))
	{
		ClearCin();
		std::cout << ERROR_MESSAGE_GENERAL;
	}
}
#endif
