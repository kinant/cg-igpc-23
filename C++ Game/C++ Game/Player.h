#pragma once
#include<iostream>

using std::cout;

#include "Point.h"

class Player 
{	
	private:
		Point m_Position;
		bool m_bHasKey;

	public:
		Player();
		~Player();

		int GetXPosition() const;
		int GetYPosition() const;

		void SetPosition(int X, int Y);

		bool HasKey() const;
		void PickupKey();
		void UseKey();

		void Draw() const;

		static constexpr char kPlayerSymbol = '@';

		int* GetXpositionPointer() { return &m_Position.X; }
		int* GetYpositionPointer() { return &m_Position.Y; }
};