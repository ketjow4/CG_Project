#include "Wave.h"

Wave::~Wave()
{
	std::list<Enemy*>::iterator it = enemyList->begin();
	while (it != enemyList->end())
			delete *it, it = enemyList->erase(it);
}

Wave::Wave(list<Enemy*>* list, Pipeline *p, int pathDifference)
	: enemyList(list), p(p), pathDifference(pathDifference)
{}


void Wave::UpdatePosition()
{
	static int j = 0;

	if( j >= enemyList->size())
	{
		j = enemyList->size() - 1;
	}

	std::list<Enemy*>::iterator it = enemyList->begin();
	for (int i = 0; it != enemyList->end(); ++it, ++i)
	{
		if((*it)->pathIndex > pathDifference && j < enemyList->size() - 1)
		{
			j++;
			break;
		}
		if( i > j)
			break;
		(*it)->UpdatePosition(p);
	}

}

void Wave::ClearDead()
{
	std::list<Enemy*>::iterator it = enemyList->begin();
	while(it != enemyList->end())
	{
		if ((*it)->HP <= 0)
			delete *it,it = enemyList->erase(it);
		else
			++it;
	}
}
