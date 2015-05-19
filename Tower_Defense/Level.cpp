#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
	delete currentWave;
	delete path;
}

//deprecated to be deleted in future
void Level::Load()
{
	//terrain = new Terrain();
	//terrain->Init("Models/terrain1.bmp", 0.3f);
	terrain = TerrainsContainer::Get(1);

	//path = new Path();
	//path->Init("Models/path1.bmp");
	path = PathsContainer::Get(1);

	list<Enemy*> *enList;		//remember to add destructor

	enList = new list<Enemy*>();
	for(int i = 0; i < 3; i++)
	{
		Enemy *en = new Enemy();
		en->light = Engine::getEngine().getLight();
		en->LoadModel(1);
		en->terrain = terrain;
		en->path = path;
		enList->push_back(en);
	}

	currentWave = new Wave(enList, 0, 50);

	list<Enemy*> *enList2;		//remember to add destructor
	enList2 = new list<Enemy*>();
	
	for(int i = 0; i < 5; i++)
	{
		enList = new list<Enemy*>();
		Enemy *en = new Enemy();
		en->light = Engine::getEngine().getLight();
	en->LoadModel(1);
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
	std::ifstream file;
	file.open(filename, std::ios::in);
	if(file.good())
	{
		string temp;
		string levelNum;
		file >> levelNum;
		levelNumber = stoi(levelNum);
		getline(file,temp);			//get rid of comment
		string terrainFile;
		string terrainElevation;
		file >> terrainFile;
		getline(file,temp);			//get rid of comment
		file >> terrainElevation;
		getline(file,temp);			//get rid of comment
		//terrain = new Terrain();
		//terrain->Init(&terrainFile[0u], stod(terrainElevation));
		terrain = TerrainsContainer::Get(1);

		string pathFile;
		file >> pathFile;
		getline(file,temp);			//get rid of comment
		//path = new Path();
		//path->Init(&pathFile[0u]);
		path = PathsContainer::Get(1);

		string waveCount;
		file >> waveCount;
		getline(file,temp);			//get rid of comment

		for(int i = 0; i < stoi(waveCount); i++)
		{
			list<Enemy*> *enList;			//remember to add destructor
			enList = new list<Enemy*>();
			string enemyCount;
			file >> enemyCount;
			getline(file,temp);			//get rid of comment
			for(int i = 0; i < stoi(enemyCount); i++)
			{
				Enemy *en = new Enemy();
				en->light = Engine::getEngine().getLight();
				en->LoadModel(1);
				en->terrain = terrain;
				en->path = path;
				enList->push_back(en);
			}
			Wave* wave = new Wave(enList, 0, 50);
			waveList.push_back(wave);
		}
		currentWave = *waveList.begin();
		file.close();
	}
	else
		std::cout << "Error reading level file " + filename << std::endl;
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

bool Level::IsWon()
{
	if(waveList.size() == 1 && (*waveList.begin())->enemyList->size() == 0)
		Accomplished = true;
	else
		Accomplished = false;
	return Accomplished;
}