#include "Wave.h"


Wave::Wave()
{
}

Wave::~Wave()
{
}

Wave::Wave(list<Enemy>* list, Pipeline *p)
{
	enemyList = list;
	this->p = p;
}



void Wave::UpdatePosition()
{
	static int j = 0;

	if( j >= enemyList->size())
	{
		j = enemyList->size() - 1;
	}

	std::list<Enemy>::iterator it = enemyList->begin();
	for (int i = 0; it != enemyList->end(); ++it, ++i)
	{
		if(it->pathIndex > pathDifference && j < enemyList->size() - 1)
		{
			j++;
			break;
		}
		if( i > j)
			break;
		it->UpdatePosition(p);
	}

}

void Wave::ClearDead()
{
	std::list<Enemy>::iterator it = enemyList->begin();
	while(it != enemyList->end())
	{
		if (it->HP <= 0)
		{
			it = enemyList->erase(it);
			//Player::getPlayer().money += 10;
		}
		else
			++it;
	}
	//vector<Enemy>* newList;
	//newList = new vector<Enemy>();
	//for(int i = 0; i < enemyList->size(); i++)
	//{
	//	if( enemyList->at(i)->HP > 0)					//check this
	//		newList->push_back(enemyList->at(i));
	//}
	//enemyList->clear();
	//enemyList = newList;
}