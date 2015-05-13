#ifndef WAVE_H
#define WAVE_H


#include "Enemy.h"
#include <vector>
#include <list>
#include "Player.h"

class Wave
{
public:
	list<Enemy*>* enemyList;
	Pipeline *p;

	Wave(list<Enemy*>* list, Pipeline *p, int pathDifference);
	~Wave();
	void UpdatePosition();
	void ClearDead();

private:
	//the differenc in path index between 2 enemies in wave
	int pathDifference;
};





#endif