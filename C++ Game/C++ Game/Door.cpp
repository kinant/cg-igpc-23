#include "Door.h"

Door::Door(int X, int Y, int ClosedColor, int OtherColor)
	: AActor(X, Y)
	, m_bIsOpen(false)
	, m_ClosedColor(ClosedColor)
{

}

void Door::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (m_bIsOpen) 
	{
		SetConsoleTextAttribute(console, m_Color);
	}
	else 
	{
		SetConsoleTextAttribute(console, m_ClosedColor);
	}
	std::cout << DOR;

	SetConsoleTextAttribute(console, kRegularColor);
}