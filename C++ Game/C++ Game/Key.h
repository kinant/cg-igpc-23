#pragma once
#include "AActor.h"

class Key : public AActor {
	public:
		Key(int X, int Y, ActorColor Color)
			: AActor(X, Y, Color) 
		{
		
		}

		virtual ActorType GetType() override { return ActorType::Key; }
		virtual void Draw() override;
};