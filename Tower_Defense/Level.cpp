#include "Level.h"

Level::Level()
	: currentWave(0)
{}

Level::~Level()
{
	delete currentWave;
}

bool Level::LoadFromFile(const string &filename)
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

		for (int i = 0, ie = stoi(waveCount); i < ie; ++i)
		{
			list<Enemy*> *enList;	//remember to add destructor
			enList = new list<Enemy*>();
			string enemyCount;
			file >> enemyCount;
			getline(file,temp);		//get rid of comment
			for (int j = 0, je = stoi(enemyCount); j < je; ++j)
			{
				Enemy *en = new Enemy();
				en->SetSimpleModel( Engine::GetEngine()->GetSimpleModel() );
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
		return true;
	}
	return false;
}


void Level::AdvanceToNextWave()
{
	if (waveList.size() <= 1)
		return;
	std::list<Wave*>::iterator it = waveList.begin();
	if ((*it)->activeEnemies->size() == 0 && (*it)->inactiveEnemies->size() == 0)//last wave should not be deleted for now
		delete *it, it = waveList.erase(it);
	currentWave = *it;
}

bool Level::IsWon()
{
	if (waveList.size() == 1 && 
		(*waveList.begin())->activeEnemies->size() == 0 && 
		(*waveList.begin())->inactiveEnemies->size() == 0)
		Accomplished = true;
	else
		Accomplished = false;
	return Accomplished;
}

string Level::Filename(int level)
{
	ostringstream oss;
	oss << "Levels/level" << level << ".txt";
	return oss.str();
}
