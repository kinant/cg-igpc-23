#include <iostream>
#include "Goal.h"

Goal::Goal(int X, int Y) 
	: AActor(X, Y)
{

}

void Goal::Draw() 
{
	std::cout << "X";
}