#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
	delete currentWave;
	delete path;
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
		int terrainKey;
		string terrainElevation;
		file >> terrainKey;
		getline(file,temp);			//get rid of comment
		terrain = TerrainsContainer::Get(terrainKey);

		int pathKey;
		file >> pathKey;
		getline(file,temp);			//get rid of comment
		path = PathsContainer::Get(pathKey);
		occupiedTowerPoints.clear();

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
				en->SetLight( Engine::getEngine().getLight() );
				en->LoadModel(1);
				en->SetTerrain(terrain);
				en->SetPath(path);
				enList->push_back(en);
			}
			Wave* wave = new Wave(enList, 0, 50,cam);
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