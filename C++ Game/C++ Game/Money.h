#pragma once
#include "AActor.h"

class Money : public AActor 
{
	public:
		Money(int X, int Y, int Worth);

		int GetWorth() const { return m_Worth; }

		virtual void Draw() override;

	private:
		int m_Worth;
};
