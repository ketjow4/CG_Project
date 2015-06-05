#include "Wave.h"

Wave::~Wave()
{
	std::list<Enemy*>::iterator it = enemyList->begin();
	while (it != enemyList->end())
			delete *it, it = enemyList->erase(it);
}

Wave::Wave(list<Enemy*>* list, Pipeline *p, int pathDifference, Camera* c)
	: enemyList(list), p(p), pathDifference(pathDifference), j(0), cam(c)
{}


void Wave::UpdatePosition()
{
	std::list<Enemy*>::iterator it = enemyList->begin();
	for (int i = 0; it != enemyList->end(); ++it, ++i)
	{
		if(i == j && (*it)->GetPathIndex() > pathDifference)
			j++;
		if(i > j)
			break;
		(*it)->UpdatePosition(p, cam);
	}

}

void Wave::ClearDead()
{
	std::list<Enemy*>::iterator it = enemyList->begin();
	while(it != enemyList->end())
	{
		if ((*it)->HP <= 0)
		{
			delete *it,it = enemyList->erase(it);
			Player::getPlayer().money += 10;	
		}
		else
			++it;
	}
}

void Wave::Render()
{
	std::list<Enemy*>::iterator it = enemyList->begin();
	for (int i = 0; it != enemyList->end(); ++it, ++i)
	{
		(*it)->model->Render();
	}
}