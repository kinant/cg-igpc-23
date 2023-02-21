/*
	CGSpectrum IGPC Cert T1
	Week 04 Challenge 3 - Class to be used to validate user input (So that I don't have to re-write code).
	It only has basic functionality right now, but I hope to extend it, and keep adding to it.
	By: Kinan Turman. 2023

	Used the following resources as help:
	- https://stackoverflow.com/questions/7345956/advantages-of-classes-with-only-static-methods-in-c
	- https://stackoverflow.com/questions/5373107/how-to-implement-static-class-member-functions-in-cpp-file
	- https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl

*/

#pragma once

#include <iostream>
#include <string>
#include<limits>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace UInput
{
	static const std::string ERROR_MESSAGE_GENERAL = "Invalid input. Try again: ";
	static const std::string ERROR_MESSAGE_BOUNDS = "Input is out of bounds. Try again: ";
	static const long long MAX_STREAM_SIZE = std::numeric_limits<std::streamsize>::max();

	/*
	* The purpose of this class is to get user input from the console, and validate that it is correct.
	* It uses mainly static template functions so that it works with any data type of user input (int, char, string, etc).
	*/

	class UserInput
	{
	public:
		// static function definitions
		template<typename T> static void GetUserInput(T& Input, string PromptMessage);

		template<typename T> static void GetUserInputRange(T& Input, string PromptMessage,
			const int& min, const int& max);

	private:
		/*
		* Private Function: ClearCin()
		* Clears the error flag on cin and ignores the max number of stream size characters
		*/
		static void ClearCin()
		{
			cin.clear();
			cin.ignore(MAX_STREAM_SIZE, '\n');
		}
	};

	/*
	* Function - GetUserInput
	* Continously prompts user for input until the proper generic type is inputted.
	* @param Input				- a reference to the input variable which we will get user input from.
	*							it is a generic type, so that it works with all types that a user can input.
	*							This is also helpful because it helps determine wether cin fails or not.
	* @param PromptMessage		- message to show the user when prompting for input.
	*/
	template<typename T> void UserInput::GetUserInput(T& Input, string PromptMessage)
	{
		cout << PromptMessage;

		// loop while as long as input is invalid
		// more info: https://stackoverflow.com/questions/34395801/how-is-stdcinvalue-evaluated-in-a-while-loop
		while (!(cin >> Input))
		{
			ClearCin();
			cout << ERROR_MESSAGE_GENERAL;
		}
		// Call ClearCin so that we ignore any other possible valid values in the stream.
		// For instance, if you input 5.5 for an integer, it will take 5 and .5 as valid inputs.
		ClearCin();
	}

	/*
	* Function - GetUserInputRnage
	* Continously prompts user for input until the proper generic type is inputted, and makes sure it is
	* within a range given by [Min, Max].
	* @param Input				- a reference to the input variable which we will get user input from.
	*							it is a generic type, so that it works with all types that a user can input.
	*							This is also helpful because it helps determine wether cin fails or not.
	* @param PromptMessage		- message to show the user when prompting for input.
	* @param Min				- Minimum value of the range to check.
	* @param Max				- Maximum value of the range to check
	*/
	template<typename T> void UserInput::GetUserInputRange(T& Input, std::string PromptMessage, const int& Min, const int& Max)
	{
		std::cout << PromptMessage << " between " << Min << " and " << Max << ": ";

		bool bIsValidInput = false;

		// loop while input is invalid
		while (!bIsValidInput)
		{
			cin >> Input;

			// check first if the input failed for some reason (ie. input a character for a number)
			if (cin.fail())
			{
				ClearCin();
				cout << ERROR_MESSAGE_GENERAL;
				bIsValidInput = false;
				continue;
			}
			// second, check that input is within range
			else if (Input < Min || Input > Max)
			{
				cout << ERROR_MESSAGE_BOUNDS;
				ClearCin();
				bIsValidInput = false;
				continue;
			}
			// else, the input is valid, exit loop
			else
			{
				bIsValidInput = true;
			}
		}

		ClearCin();
	}
}

