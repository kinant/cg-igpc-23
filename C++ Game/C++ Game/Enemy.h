#pragma once
#include <iostream>
#include "AActor.h"

class Enemy : public AActor 
{
	public:
		Enemy(int X, int Y, int DeltaX = 0, int DeltaY = 0);

		virtual void Draw() override;
		virtual void Update() override;

	private:
		int m_MovementInX;
		int m_MovementInY;

		int m_CurrentMovementX;
		int m_CurrentMovementY;

		int m_DirectionX;
		int m_DirectionY;

		void UpdateDirection(int& Current, int& Direction, int& Movement);
};