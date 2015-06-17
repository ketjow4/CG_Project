#pragma once

#include <iostream>
#include <map>

#include "math_3d.h"
#include "Model.h"
#include "SimpleModelTechnique.h"
#include "Path.h"
#include "Terrain.h"
#include "pipeline.h"
#include "ModelsContainer.h"
#include "Player.h"
#include "Camera.h"


class Enemy
{

public:
	Mesh *model;
	double HP;
	double Attack;
	int effectId;

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
	const int& GetPathIndex() const;
	Vector3f GetFuturePosition(int steps) const;
	void SetSimpleModel(SimpleModelTechnique* simpleModel);
	void SetTerrain(Terrain* terrain);
	void SetPath(Path* path);
	
private:
	const static float EffectIntensity[2];
	const static Vector4f EffectColor[2];
	Vector3f position;
	Vector3f rotation;
	int pathIndex;
	SimpleModelTechnique* simpleModel;
	Path* path;
	Terrain* terrain;
};
