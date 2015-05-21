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
#include "Camera.h"


class Enemy
{

public:
	Vector3f position;
	Vector3f rotation;
	BasicLightingTechnique* light;
	Path* path;
	Terrain* terrain;
	Mesh *model;
	int pathIndex;
	double HP;
	double Attack;
	int effectId;
	Camera* cam;
	struct Poison
	{
		int duration;
		int degenFreq;
	} poison;

	Enemy();
	~Enemy();
	void LoadModel(int id);
	void UpdatePosition(Pipeline *p, Camera* cam);
	const Vector3f& GetPosition() const;
	const Vector3f& GetRotation() const;

	Vector3f GetFuturePosition(int steps) const;
private:
	const static float EffectIntensity[2];
	const static Vector4f EffectColor[2];
};

#endif