#pragma once
#include "Terrain.h"

#include <map>

class TerrainsContainer
{
public:
	static void LoadTerrain(int key, const string &heightMap, const string &texture, float heightFactor);
	static Terrain* Get(int key);
	static void FreeResources();
private:
	static map<int, Terrain*> terrains;

	TerrainsContainer();
	~TerrainsContainer();
};

