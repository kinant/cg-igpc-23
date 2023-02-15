#include <iostream>
#include <string>
#include<limits>

#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H
class InputValidator
{
public:
	static void GetUserInput(int& input);
	std::string error = "Invalid input! Please try again: ";
private:
	template<class T> static void GenericUserInput(T& input);

	static void ClearCin() 
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
#endif
