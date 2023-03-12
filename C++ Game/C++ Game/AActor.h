#pragma once
#include "Point.h"

enum class ActorColor 
{
	Regular = 7,
	Blue = 9,
	Green = 10,
	Red = 12,
	SolidGreen = 34,
	SolidRed = 68,
	SolidBlue = 153
};

class AActor 
{
	public:
		AActor(int X, int Y, ActorColor = ActorColor::Regular);
		virtual ~AActor();

		int GetXPosition();
		int GetYPosition();
		int* GetXPositionPointer();
		int* GetYPositionPointer();
		void SetPosition(int X, int Y);

		ActorColor GetColor() { return m_Color; }

		void Remove() { m_bIsActive = false; }
		bool IsActive() { return m_bIsActive;  }
		void Place(int X, int Y);

		virtual void Draw() = 0;

		virtual void Update() 
		{
			
		}

	protected:
		Point* m_pPosition;

		bool m_bIsActive;
		ActorColor m_Color;
};