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
	Wave * wave;

	void Load();

private:

};





#endif