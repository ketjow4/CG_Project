#ifndef ENEMY_H
#define ENEMY_H


#include <iostream>
#include "math_3d.h"
#include "Model.h"
#include "basic_lighting.h"
#include "Engine.h"


class Enemy
{
public:
	Enemy();
	~Enemy();

	Vector3f position;
	Mesh  model;
	BasicLightingTechnique* light;
	Path* path;
	Terrain* terrain;
	int pathIndex;
	double HP;
	double Attack;

	void LoadModel(string filename);


	void UpdatePosition(Pipeline *p);

	Vector3f GetPosition();


private:

};




#endif