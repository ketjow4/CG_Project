#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:

	~Player() {}

	static int Lives;
	static int money;

	void AddMoneyWaveCompleted(int howMany);

	void TowerBuy();

	void LooseLive(int attackStrengh);

	static Player getPlayer()
	{
		static Player p;
		return p;
	}


private:
	Player() {}
	Player(const Player &p) {}

	
};







#endif