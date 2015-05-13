#ifndef WAVE_H
#define WAVE_H


#include "Enemy.h"
#include <vector>
#include <list>
#include "Player.h"

class Wave
{
public:
	Wave();
	~Wave();

	Wave(list<Enemy>* list, Pipeline *p);

	list<Enemy>* enemyList;
	//the differenc in path index between 2 enemies in wave
	int pathDifference;

	Pipeline *p;

	void UpdatePosition();

	void ClearDead();

private:

};





#endif