#pragma once

#include <list>
#include "Wave.h"
#include "TerrainsContainer.h"
#include "PathsContainer.h"
#include "Engine.h"
#include "Tower.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Camera.h"

class Level
{
public:
	/** Obecny teren */
	Terrain* terrain;
	/** Obecna �cie�ka */
	Path* path;
	/** Kamera */
	Camera* cam;
	/** Obecna fala */
	Wave * currentWave;
	/** Ustawione wie�e */
	vector<Tower*> towerList;
	/** Pozycje zaj�te ju� przez wie�e */
	set<pair<float, float>> occupiedTowerPoints;
	/** Fale na danym poziomie */
	list<Wave*> waveList;
	/** Numer poziomu*/
	int levelNumber;

	Level();
	~Level();
	/**
	* Funkcja sprawdza czy mo�na przej�� do nast�pnej fali, je�eli tak to przechodzi.
	*/
	void AdvanceToNextWave();
	/**
	* Funkcja zwraca czy poziom zosta� uko�czony pomy�lnie.
	*/
	bool IsWon();
	/**
	* Funkcja �aduje poziom z pliku.
	* @param filename plik z opisem poziomu
	*/
	bool LoadFromFile(const string &filename);
	/**
	* Funkcja zwraca nazwe pliku dla danego poziomu.
	* @param level poziom
	*/
	static string Filename(int level);
private:
	bool Accomplished;
};

