#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::Load()
{
	list<Enemy*> enList;

	Enemy *en = new Enemy();
	en->light = Engine::getEngine().getLight();
	en->LoadModel(1, "Models/phoenix_ugv.md2");
	en->terrain = terrain;
	en->path = path;
	enList.push_back(en);
	
	en = new Enemy();
	en->light = Engine::getEngine().getLight();
	en->LoadModel(1, "Models/phoenix_ugv.md2");
	en->terrain = terrain;
	en->path = path;
	enList.push_back(en);

	en = new Enemy();
	en->light = Engine::getEngine().getLight();
	en->LoadModel(1, "Models/phoenix_ugv.md2");
	en->terrain = terrain;
	en->path = path;
	enList.push_back(en);

	wave = new Wave(&enList, 0, 50);

}