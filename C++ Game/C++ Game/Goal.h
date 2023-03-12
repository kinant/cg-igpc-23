#pragma once
#include "AActor.h"

class Goal : public AActor 
{
	public:
		Goal(int X, int Y);
		
		virtual ActorType GetType() override { return ActorType::Goal; }
		virtual void Draw() override;
};