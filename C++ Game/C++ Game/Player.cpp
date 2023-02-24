#include "Player.h"

Player::Player()
	: m_bHasKey(false)
{

}

Player::~Player() 
{

}

int Player::GetXPosition() const
{
	return m_Position.X;
}

int Player::GetYPosition() const
{
	return m_Position.Y;
}

void Player::SetPosition(int X, int Y) 
{
	m_Position.X = X;
	m_Position.Y = Y;
}

bool Player::HasKey() const
{
	return m_bHasKey;
}
void Player::PickupKey() 
{
	m_bHasKey = true;
}

void Player::UseKey() 
{
	m_bHasKey = false;
}

void Player::Draw() const
{
	cout << kPlayerSymbol;
}