#pragma once
#include "AActor.h"

class Door : public AActor
{
public:
	Door(int X, int Y, ActorColor ClosedColor, ActorColor OtherColor);

	virtual void Draw() override;

	bool IsOpen() { return m_bIsOpen; }
	void Open() { m_bIsOpen = true; }
	ActorColor GetColor() { return m_ClosedColor;  }

private:
	bool m_bIsOpen;
	ActorColor m_ClosedColor;
	static constexpr char DOR = (char)219;
};