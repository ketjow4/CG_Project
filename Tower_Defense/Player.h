#ifndef PLAYER_H
#define PLAYER_H



class Player
{
public:
	Player();
	~Player();

	int Lives;
	int money;

	void AddMoneyWaveCompleted(int howMany);

	void TowerBuy();

	void LooseLive();

private:

};







#endif