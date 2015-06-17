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
	/** Przeciwnicy czekaj�cy na wst�p do mapy */
	list<Enemy*>* inactiveEnemies;
	/** Potok */
	Pipeline *p;
	/** Kamera */
	Camera* cam;

	/**
	* Twory fal� przeciwnik�w.
	* @param list przeciwnicyw danej fali
	* @param p potok
	* @param pathDifference odleg�o�� mi�dzy dwoma kolejnymi przeciwnikami na �cie�ce
	* @param c kamera
	*/
	Wave(list<Enemy*>* list, Pipeline *p, int pathDifference, Camera* c);
	~Wave();
	/**
	* Funkcja aktualizuje pozycje i wy�wietla przeciwnik�w, aktywuje przeciwnik�w w odpowiednim momencie. 
	*/
	void UpdatePosition();
	/**
	* Funkcja zwalnia zasoby po pokonanych przeciwnikach.
	*/
	void ClearDead();
	/**
	* Funkcja tylko wy�wietla aktywnych przeciwnik�w.
	*/
	void Render();
private:
	//the differenc in path index between 2 enemies in wave
	int pathDifference;
	int currentPathDifference;

	void ActivateNextEnemy();
};
