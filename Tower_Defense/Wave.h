#pragma once

#include "Enemy.h"
#include <vector>
#include <list>
#include "Player.h"
#include "Camera.h"

class Wave
{
public:
	/** Przeciwnicy na mapie */
	list<Enemy*>* activeEnemies;
	/** Przeciwnicy czekaj¹cy na wstêp do mapy */
	list<Enemy*>* inactiveEnemies;
	/** Potok */
	Pipeline *p;
	/** Kamera */
	Camera* cam;

	/**
	* Twory falê przeciwników.
	* @param list przeciwnicyw danej fali
	* @param p potok
	* @param pathDifference odleg³oœæ miêdzy dwoma kolejnymi przeciwnikami na œcie¿ce
	* @param c kamera
	*/
	Wave(list<Enemy*>* list, Pipeline *p, int pathDifference, Camera* c);
	~Wave();
	/**
	* Funkcja aktualizuje pozycje i wyœwietla przeciwników, aktywuje przeciwników w odpowiednim momencie. 
	*/
	void UpdatePosition();
	/**
	* Funkcja zwalnia zasoby po pokonanych przeciwnikach.
	*/
	void ClearDead();
	/**
	* Funkcja tylko wyœwietla aktywnych przeciwników.
	*/
	void Render();
private:
	//the differenc in path index between 2 enemies in wave
	int pathDifference;
	int currentPathDifference;

	void ActivateNextEnemy();
};
