#include "Player.h"
#include "Key.h"

Player::Player() 
	: AActor(0, 0)
	, m_pCurrentKey(nullptr)
	, m_Money(0)
	, m_Lives(kStartingNumberOfLives)
{

}

bool Player::HasKey() 
{
	return (m_pCurrentKey != nullptr);
}

bool Player::HasKey(int Color) 
{
	return (HasKey() && m_pCurrentKey->GetColor() == Color);
}

void Player::PickupKey(Key* Key) 
{
	m_pCurrentKey = Key;
}

void Player::DropKey() 
{
	if (m_pCurrentKey) 
	{
		m_pCurrentKey->Place(m_pPosition->X, m_pPosition->Y);
		m_pCurrentKey = nullptr;
	}
}

void Player::Draw()
{
	std::cout << kPlayerSymbol;
}