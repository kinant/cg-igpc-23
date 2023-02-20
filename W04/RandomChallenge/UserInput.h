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

	class UserInput
	{
	public:
		template<typename T> static void GetUserInput(T& input, string promptMessage);

		template<typename T> static void GetUserInputRange(T& input, string promptMessage,
			const int& min, const int& max);

	private:

		static void ClearCin()
		{
			cin.clear();
			cin.ignore(MAX_STREAM_SIZE, '\n');
		}
	};

	template<typename T> void UserInput::GetUserInput(T& input, string promptMessage)
	{
		cout << promptMessage;

		while (!(cin >> input))
		{
			ClearCin();
			cout << ERROR_MESSAGE_GENERAL;
		}
	}

	template<typename T> void UserInput::GetUserInputRange(T& input, std::string promptMessage, const int& min, const int& max)
	{
		std::cout << promptMessage << " between " << min << " and " << max << ": ";

		bool bIsValidInput = false;

		while (!bIsValidInput)
		{
			cin >> input;

			if (cin.fail())
			{
				ClearCin();
				cout << ERROR_MESSAGE_GENERAL;
				bIsValidInput = false;
				continue;
			}
			else if (input < min || input > max)
			{
				cout << ERROR_MESSAGE_BOUNDS;
				ClearCin();
				bIsValidInput = false;
				continue;
			}
			else
			{
				bIsValidInput = true;
			}
		}
	}
}

#pragma once
