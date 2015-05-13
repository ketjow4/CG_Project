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
	this->Lives -= attackStrengh;
	if(Lives < 0)
		Lives = 0;
}

int Player::Lives = 10;
int Player::money = 0;
