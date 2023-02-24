#pragma once
#include "AActor.h"
#include <iostream>
#include <Windows.h>

class Key : public AActor {
	public:
		Key(int X, int Y, int Color)
			: AActor(X, Y, Color) 
		{
		
		}

		virtual void Draw() override;
};