#include "Player.h"



void Player::AddMoneyWaveCompleted(int howMany)
{
	this->money += howMany; 
}

void Player::TowerBuy()
{
	money -= 10;
}

void Player::LooseLive(int attackStrengh)
{
	this->lives -= attackStrengh;
	if(lives < 0)
		lives = 0;
}

void Player::Init(int lives, int money)
{
	this->lives = lives;
	this->money = money;
}

int Player::lives = 0;
int Player::money = 0;
