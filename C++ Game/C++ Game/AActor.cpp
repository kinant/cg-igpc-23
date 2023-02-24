#include "AActor.h"

AActor::AActor(int X, int Y, int Color) 
	: m_pPosition(new Point(x, y))
	, m_bIsActive(true)
	, m_Color(Color)
{
	
}

AActor::~AActor() 
{
	delete m_pPosition;
	m_pPosition = nullptr;
}

int AActor::GetXPosition() 
{
	return m_pPosition->X;
}

int AActor::GetYPosition() 
{
	return m_pPosition->Y;
}

int* AActor::GetXPositionPointer() 
{
	return &(m_pPosition->X);
}

int* AActor::GetYPositionPointer() 
{
	return &(m_pPosition->Y);
}

void AActor::SetPosition(int X, int Y) 
{
	m_pPosition->X = X;
	m_pPosition->Y = Y;
}

void AActor::Place(int X, int Y) 
{
	AActor::SetPosition(X, Y);
	m_bIsActive = true;
}