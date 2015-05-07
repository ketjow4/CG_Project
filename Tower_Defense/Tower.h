#ifndef TOWER_H
#define TOWER_H

#include "Model.h"
//#include "WorldObject.h"
#include "skinned_mesh.h"
#include "skinning_technique.h"
#include "basic_lighting.h"
#include "Engine.h"
#include "Enemy.h"


class Tower				//: public WorldObject
{
public:
	Tower();
	~Tower();


	Tower(BasicLightingTechnique* light, SkinningTechnique* m_pEffect, Vector3f position, Terrain* ter);

	SkinnedMesh Model3D;
	Mesh Missile;
	//float missileLife; not used
	double Range;
	Vector3f missilePos;
	Vector3f towerPos;
	double distance_to_target;
	double towerHeight;			//only good when scale is 5
	double towerScale;
	Enemy* enemy;


	BasicLightingTechnique* light;
	SkinningTechnique* m_pEffect;
	Terrain* terrain;
	



	void Shoot(Pipeline * p, Enemy* en);

	void CalcAnimation();

	void LoadModel(string filename);

	void LoadMissile(string filename);

	void Render(Pipeline *p);

	bool IsInRange(Vector3f enemyPos);

private:

	void LimitTowerPosition();


};


#endif