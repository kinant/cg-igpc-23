#pragma once
#include "Point.h"

static constexpr int kGreenColor = 10;
static constexpr int kGreenColorSolid = 34;
static constexpr int kRedColor = 12;
static constexpr int kRedColorSolid = 68;
static constexpr int kBlueColor = 9;
static constexpr int kBlueColorSolid = 153;
static constexpr int kRegularColor = 7;

class AActor 
{
	public:
		AActor(int X, int Y, int Color = kRegularColor);
		virtual ~AActor();

		int GetXPosition();
		int GetYPosition();
		int* GetXPositionPointer();
		int* GetYPositionPointer();
		void SetPosition(int X, int Y);

		int GetColor() { return m_Color; }
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
		int m_Color;
};