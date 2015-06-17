#pragma once

class Player
{
public:
	/** Pozosta³a liczba ¿yæ */
	static int lives;
	/** Aktualna wartoœæ posiadanych pieniêdzy */
	static int money;

	~Player() {}
	/**
	* Funkcja pobiera op³atê za ustawienie wie¿y.
	*/
	void TowerBuy();
	/**
	* Funkcja odbiera ¿ycie w zale¿noœci od si³y ataku przeciwnika.
	* @param attackStrengh 
	*/
	void LooseLive(int attackStrengh);
	/**
	* Funkcja ustawia parametry gracza.
	* @param lives liczba ¿yc
	* @param money pieni¹dze
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
