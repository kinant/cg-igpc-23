#pragma once
#include <iostream>
#include <Windows.h>

#include "AActor.h"

class Door : public AActor
{
	public:
		Door(int X, int Y, int ClosedColor);
		
		virtual void Draw() override;

		bool IsOpen() { return m_bIsOpen; }
		void Open() { m_bIsOpen = true; }

	private:
		bool m_bIsOpen;
		int m_ClosedColor;
}