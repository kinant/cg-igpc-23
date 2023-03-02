#pragma once
#include <iostream>
#include <Windows.h>

#include "AActor.h"

class Door : public AActor
{
public:
	Door(int X, int Y, int ClosedColor, int OtherColor);

	virtual void Draw() override;

	bool IsOpen() { return m_bIsOpen; }
	void Open() { m_bIsOpen = true; }
	int GetColor() { return m_ClosedColor;  }

private:
	bool m_bIsOpen;
	int m_ClosedColor;
	static constexpr char DOR = (char)219;
};