#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
	delete currentWave;
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
	for(int i = 0; i < 3; i++)
	{
		Enemy *en = new Enemy();
		en->light = Engine::getEngine().getLight();
		en->LoadModel(1, "Models/phoenix_ugv.md2");
		en->terrain = terrain;
		en->path = path;
		enList->push_back(en);
	}

	currentWave = new Wave(enList, 0, 50);

	list<Enemy*> *enList2;		//remember to add destructor
	enList2 = new list<Enemy*>();
	
	for(int i = 0; i < 15; i++)
	{
		enList = new list<Enemy*>();
		Enemy *en = new Enemy();
		en->light = Engine::getEngine().getLight();
		en->LoadModel(1, "Models/phoenix_ugv.md2");
		en->terrain = terrain;
		en->path = path;
		enList2->push_back(en);
	}
	Wave* wave2 = new Wave(enList2, 0, 50);

	waveList.push_back(currentWave);
	waveList.push_back(wave2);
}

void Level::LoadFromFile(string filename)
{
	//TODO implement loading level from file
}

void Level::AdvanceToNextWave()
{
	std::list<Wave*>::iterator it = waveList.begin();
	if ((*it)->enemyList->size() == 0 && waveList.size() != 1)			//last wave should not be deleted for now
	{
		delete *it,it = waveList.erase(it);

	}
	currentWave = *(waveList.begin());
}