#ifndef WAVE_H
#define WAVE_H


#include "Enemy.h"
#include <vector>
#include <list>
#include "Player.h"
#include "Camera.h"

class Wave
{
public:
	list<Enemy*>* enemyList;
	Pipeline *p;
	Camera* cam;

	Wave(list<Enemy*>* list, Pipeline *p, int pathDifference, Camera* c);
	~Wave();
	void UpdatePosition();
	void ClearDead();

	void Render();

private:
	//the differenc in path index between 2 enemies in wave
	int pathDifference;
	int j;	//to proper position update TODO: name it better
};





#endif