#include "Player.h"


Player::Player()
{
}

Player::~Player()
{
}

void Player::AddMoneyWaveCompleted(int howMany)
{
	this->money += howMany; 
}

void Player::TowerBuy()
{
	;		//implement later
}

void Player::LooseLive()
{
	this->Lives -= 1;
}