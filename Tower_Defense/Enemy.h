#ifndef ENEMY_H
#define ENEMY_H


#include <iostream>
#include <map>

#include "math_3d.h"
#include "Model.h"
#include "BasicLighting.h"
#include "Path.h"
#include "Terrain.h"
#include "pipeline.h"
#include "ModelsContainer.h"
#include "Player.h"


class Enemy
{
public:
	Enemy();
	~Enemy();

	Vector3f position;
	BasicLightingTechnique* light;
	Path* path;
	Terrain* terrain;
	int pathIndex;
	double HP;
	double Attack;
	int effectId;

	void LoadModel(int id);

	void UpdatePosition(Pipeline *p);

	Vector3f GetPosition();
	Vector3f GetFuturePosition(int steps);

private:
	Mesh *model;
	const static float EffectIntensity[2];
	const static Vector4f EffectColor[2];
};

#endif