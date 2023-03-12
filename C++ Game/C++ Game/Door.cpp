#include <iostream>
#include <Windows.h>

#include "Door.h"

Door::Door(int X, int Y, ActorColor ClosedColor, ActorColor OtherColor)
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
		SetConsoleTextAttribute(console, (int)m_Color);
	}
	else 
	{
		SetConsoleTextAttribute(console, (int)m_ClosedColor);
	}
	std::cout << DOR;

	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}