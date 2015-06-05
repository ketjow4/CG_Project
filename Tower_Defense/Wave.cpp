#include "Wave.h"

Wave::~Wave()
{
	std::list<Enemy*>::iterator it = activeEnemies->begin();
	while (it != activeEnemies->end())
			delete *it, it = activeEnemies->erase(it);
	it = inactiveEnemies->begin();
	while (it != inactiveEnemies->end())
		delete *it, it = inactiveEnemies->erase(it);
}

Wave::Wave(list<Enemy*>* list, Pipeline *p, int pathDifference, Camera* c)
	: activeEnemies(new std::list<Enemy*>()), inactiveEnemies(list),
	p(p), cam(c),
	pathDifference(pathDifference), currentPathDifference(-20)
{}

void Wave::UpdatePosition()
{
	std::list<Enemy*>::iterator it = activeEnemies->begin();
	if (++currentPathDifference == pathDifference)
	{
		currentPathDifference = 0;
		ActivateNextEnemy();
	}

	for (; it != activeEnemies->end(); ++it)
		(*it)->UpdatePosition(p, cam);
}

void Wave::ClearDead()
{
	std::list<Enemy*>::iterator it = activeEnemies->begin();
	while (it != activeEnemies->end())
	{
		if ((*it)->HP <= 0)
		{
			delete *it, it = activeEnemies->erase(it);
			Player::getPlayer().money += 10;	
		}
		else
			++it;
	}
}

void Wave::Render()
{
	std::list<Enemy*>::iterator it = activeEnemies->begin();
	for (; it != activeEnemies->end(); ++it)
		(*it)->model->Render();
}

void Wave::ActivateNextEnemy()
{
	if (!inactiveEnemies->empty())
	{
		Enemy* enemy = *inactiveEnemies->begin();
		inactiveEnemies->erase(inactiveEnemies->begin());
		activeEnemies->push_back(enemy);
	}
}
