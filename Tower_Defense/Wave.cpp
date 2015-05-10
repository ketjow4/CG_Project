#include "Wave.h"


Wave::Wave()
{
}

Wave::~Wave()
{
}

Wave::Wave(vector<Enemy*>* list, Pipeline *p)
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

	for(int i = 0; i < enemyList->size(); i++)
	{
		if(enemyList->at(j)->pathIndex > pathDifference && j < enemyList->size() - 1)
		{
			j++;
			break;
		}
		if( i > j)
			break;
		enemyList->at(i)->UpdatePosition(p);
	}

}

void Wave::ClearDead()
{
	vector<Enemy*>* newList;
	newList = new vector<Enemy*>();
	for(int i = 0; i < enemyList->size(); i++)
	{
		if( enemyList->at(i)->HP > 0)					//check this
			newList->push_back(enemyList->at(i));
	}
	enemyList->clear();
	enemyList = newList;
}