#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include "Wave.h"
#include "Terrain.h"
#include "Engine.h"
#include "Tower.h"
#include <iostream>
#include <fstream>
#include "Camera.h"

class Level
{
public:
	Level();
	~Level();

	Terrain* terrain;
	Path* path;
	Wave * currentWave;
	vector<Tower*> towerList;	//tower list for actual level
	Camera* cam;
	
	list<Wave*> waveList;
	int levelNumber;		//to chceck if this is last level

	void AdvanceToNextWave();

	bool IsWon();

	void Load();

	void LoadFromFile(string filename);

private:
	bool Accomplished;
};





#endif