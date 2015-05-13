#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include "Wave.h"
#include "Terrain.h"
#include "Engine.h"

class Level
{
public:
	Level();
	~Level();

	Terrain* terrain;
	Path* path;
	Wave * currentWave;
	
	list<Wave*> waveList;

	void AdvanceToNextWave();

	void Load();

	void LoadFromFile(string filename);

private:

};





#endif