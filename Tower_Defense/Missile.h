#pragma once
#include "math_3d.h"
#include "Enemy.h"
#include "Terrain.h"

class Missile
{
public:
	/** Pozycja pocisku w �wiecie gry */
	Vector3f pos;
	/** Pozosta�y czas �ycia */
	int lifetime;

	/**
	* Tworzy nowy pocisk.
	* @param pos pocz�tkowa pozycja pocisku
	* @param dir kierunek lotu pocisku
	* @param speed szybko�� pocisku
	* @paran lifetime czas �ycia pocisku
	*/
	Missile(const Vector3f &pos, const Vector3f &dir, float speed, int lifetime);
	~Missile();

	/**
	* Funkcja przesuwa pocisk zgodnie z kierunkiem wystrzelenia.
	*/
	void UpdateMissile();
	/**
	* Funkcja sprawdza czy zasz�a kolizja z przeciwnikiem.
	* @param enemy rozpatrywany przeciwnik
	*/
	bool Collide(Enemy *enemy) const;
	/**
	* Funkcja sprawdza czy zasz�a kolizja z terenem.
	* @param terrain rozpatrywany teren
	*/
	bool Collide(Terrain *terrain) const;
private:
	Vector3f dir;
	float speed;
};

