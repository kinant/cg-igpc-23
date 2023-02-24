#include "Key.h"

void Key::Draw() 
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, m_Color);

	std::cout << "+";

	SetConsoleTextAttribute(console, kRegularColor);
}