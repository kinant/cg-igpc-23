#pragma once
#include<iostream>
#include<Windows.h>
#include "AActor.h"

// forward class declaration
class Key;

#include "Point.h"

static constexpr char kPlayerSymbol = '@';
constexpr int kStartingNumberOfLives = 3;

class Player : public AActor
{
	public:
		Player();

		bool HasKey();
		bool HasKey(int Color);
		void PickupKey(Key* Key);
		void UseKey();
		void DropKey();

		void AddMoney(int Money) { m_Money += Money; }
		int GetMoney() { return m_Money; }

		int GetLives() { return m_Lives; };
		void DecrementLives() { m_Lives--; }

		virtual void Draw() override;

	private:
		Key* m_pCurrentKey;
		int m_Money;
		int m_Lives;
};