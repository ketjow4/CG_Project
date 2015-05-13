#pragma once

#include "Model.h"
//#include "WorldObject.h"
#include "skinned_mesh.h"
#include "skinning_technique.h"
#include "basic_lighting.h"
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

	SkinnedMesh Model3D;
	Mesh MissileMesh;
	double Range;
	Vector3f towerPos;
	double distance_to_target;
	double towerHeight;			//only good when scale is 5
	double towerScale;
	list<Missile> missiles;
	int cost;		//how many money tower cost
	int reloading;

	BasicLightingTechnique* light;
	SkinningTechnique* m_pEffect;
	Terrain* terrain;
	



	void Shoot(Enemy* en);
	void UpdateMissiles(Pipeline * p, list<Enemy*> *enemies);
	void Reload();

	void CalcAnimation();

	void LoadModel(string filename);

	void LoadMissile(string filename);

	void Render(Pipeline *p);

	bool IsInRange(Vector3f enemyPos);

	void RenderMissile(Missile *missile, Pipeline *p);
private:
	void UpdateMissile(Pipeline * p, Missile* missile, list<Enemy*> *enemies);
	void LimitTowerPosition();


};
