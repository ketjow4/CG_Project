#pragma once

class Player
{
public:

	~Player() {}

	static int lives;
	static int money;

	void AddMoneyWaveCompleted(int howMany);

	void TowerBuy();

	void LooseLive(int attackStrengh);

	void Init(int lives, int money);

	static Player getPlayer()
	{
		static Player p;
		return p;
	}


private:
	Player() {}
	Player(const Player &p) {}

	
};
