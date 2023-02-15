#include <iostream>
#include <string>
#include<limits>

#ifndef USER_INPUT_H
#define USER_INPUT_H
class InputValidator
{
public:
	
	template<class T> static void GenericUserInput(T& input, std::string promptMessage);
private:
	static void UserInput();

	static void ClearCin() 
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
#endif
