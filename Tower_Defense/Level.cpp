#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
	delete wave;
	delete path;
	delete terrain;
}

void Level::Load()
{


	terrain = new Terrain();
	terrain->Init("Models/terrain1.bmp", 0.3f);

	path = new Path();
	path->Init("Models/path1.bmp");

	list<Enemy*> *enList;		//remember to add destructor

	enList = new list<Enemy*>();
	Enemy *en = new Enemy();
	en->light = Engine::getEngine().getLight();
	en->LoadModel(1, "Models/phoenix_ugv.md2");
	en->terrain = terrain;
	en->path = path;
	enList->push_back(en);
	
	en = new Enemy();
	en->light = Engine::getEngine().getLight();
	en->LoadModel(1, "Models/phoenix_ugv.md2");
	en->terrain = terrain;
	en->path = path;
	enList->push_back(en);

	en = new Enemy();
	en->light = Engine::getEngine().getLight();
	en->LoadModel(1, "Models/phoenix_ugv.md2");
	en->terrain = terrain;
	en->path = path;
	enList->push_back(en);

	wave = new Wave(enList, 0, 50);
}