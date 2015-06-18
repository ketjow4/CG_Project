#include "Wave.h"

Wave::~Wave()
{
	if (activeEnemies)
	{
		std::list<Enemy*>::iterator it = activeEnemies->begin();
		while (it != activeEnemies->end())
			delete *it, it = activeEnemies->erase(it);
		delete activeEnemies;
	}
	if (inactiveEnemies)
	{
		std::list<Enemy*>::iterator it = inactiveEnemies->begin();
		while (it != inactiveEnemies->end())
			delete *it, it = inactiveEnemies->erase(it);
		delete inactiveEnemies;
	}
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
			if ((*it)->HP != INT32_MIN)
				Player::GetPlayer().money += 5;
			delete *it, it = activeEnemies->erase(it);
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
