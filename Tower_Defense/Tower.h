#pragma once

#include "Model.h"
//#include "WorldObject.h"
#include "SkinnedMesh.h"
#include "SkinningTechnique.h"
#include "BasicLighting.h"
#include "Engine.h"
#include "Enemy.h"
#include "Missile.h"
#include <list>


class Tower				//: public WorldObject
{
public:
	Tower();
	~Tower();


	Tower(BasicLightingTechnique* light, SkinningTechnique* m_pEffect, Vector3f position, Terrain* ter);

	
	double Range;
	Vector3f towerPos;
	double distance_to_target;
	double towerHeight;			//only good when scale is 5
	double towerScale;
	list<Missile> missiles;
	static int cost;		//how much money tower costs :p jkjk
	int reloading;

	BasicLightingTechnique* light;
	SkinningTechnique* m_pEffect;
	Terrain* terrain;

	void Shoot(Enemy* en);
	void UpdateMissiles(Pipeline * p, list<Enemy*> *enemies);
	void Reload();

	void LoadModel(int key);
	void LoadMissile(int key);

	void Render(Pipeline *p, Camera* cam);

	bool IsInRange(Vector3f enemyPos);

	void RenderMissile(Missile *missile, Pipeline *p);

	Vector3f GetPosition()
	{
		return towerPos;
	}

	Vector3f GetScale()
	{
		return Vector3f(towerScale,towerScale,towerScale);
	}

	SkinnedMesh *model;

private:
	
	Mesh *missileModel;
	int missileType;

	void CalcAnimation();
	void UpdateMissile(Pipeline * p, Missile* missile, list<Enemy*> *enemies);
	void LimitTowerPosition();
};

