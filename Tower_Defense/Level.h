#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include "Wave.h"
#include "TerrainsContainer.h"
#include "Engine.h"
#include "Tower.h"
#include <iostream>
#include <fstream>

class Level
{
public:
	Terrain* terrain;
	Path* path;
	Wave * currentWave;
	vector<Tower*> towerList;	//tower list for actual level
	list<Wave*> waveList;
	int levelNumber;		//to chceck if this is last level

	Level();
	~Level();
	void AdvanceToNextWave();
	bool IsWon();
	void Load();
	void LoadFromFile(string filename);
private:
	bool Accomplished;
};





#endif