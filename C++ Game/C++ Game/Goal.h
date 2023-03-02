#pragma once
#include <iostream>
#include "AActor.h"

class Goal : public AActor 
{
	public:
		Goal(int X, int Y);
		
		virtual void Draw() override;
};