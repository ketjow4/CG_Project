#pragma once

class Player
{
public:
	/** Pozosta�a liczba �y� */
	static int lives;
	/** Aktualna warto�� posiadanych pieni�dzy */
	static int money;

	~Player() {}
	/**
	* Funkcja pobiera op�at� za ustawienie wie�y.
	*/
	void TowerBuy();
	/**
	* Funkcja odbiera �ycie w zale�no�ci od si�y ataku przeciwnika.
	* @param attackStrengh 
	*/
	void LooseLive(int attackStrengh);
	/**
	* Funkcja ustawia parametry gracza.
	* @param lives liczba �yc
	* @param money pieni�dze
	*/
	void Init(int lives, int money);
	/**
	* Funkcja pobiera obiekt gracza;
	*/
	static Player GetPlayer()
	{
		static Player p;
		return p;
	}
private:
	Player() {}
	Player(const Player &p) {}
};
