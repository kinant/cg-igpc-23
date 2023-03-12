#include <iostream>
#include "Money.h"

Money::Money(int X, int Y, int Worth) 
	: AActor(X, Y)
	, m_Worth(Worth)
{
}

void Money::Draw() 
{
	std::cout << "$";
}