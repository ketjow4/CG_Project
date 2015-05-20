#include "TerrainsContainer.h"

map<int, Terrain*> TerrainsContainer::terrains;

TerrainsContainer::TerrainsContainer()
{}

TerrainsContainer::~TerrainsContainer()
{
	FreeResources();
}

void TerrainsContainer::FreeResources()
{
	while (!terrains.empty())
	{
		map<int, Terrain*>::iterator it = terrains.begin();
		delete it->second;
		terrains.erase(it);
	}
}

void TerrainsContainer::LoadTerrain(int key, const string &heightMap, const string &texture, float heightFactor)
{
	if (terrains.find(key) == terrains.end())
	{
		Terrain* terrain = new Terrain();
		terrain->Init(heightMap, texture, heightFactor);
		terrains.insert(make_pair(key, terrain));
	}
}

Terrain* TerrainsContainer::Get(int key)
{
	map<int, Terrain*>::iterator it = terrains.find(key);
	if (it == terrains.end())
		return 0;
	return it->second;
}