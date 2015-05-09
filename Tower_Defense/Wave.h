#ifndef WAVE_H
#define WAVE_H


#include "Enemy.h"
#include <vector>

class Wave
{
public:
	Wave();
	~Wave();

	Wave(vector<Enemy*>* list, Pipeline *p);

	vector<Enemy*>* enemyList;
	//the differenc in path index between 2 enemies in wave
	int pathDifference;

	Pipeline *p;

	void UpdatePosition();

	void ClearDead();

private:

};





#endif