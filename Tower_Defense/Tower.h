#ifndef TOWER_H
#define TOWER_H

#include "Model.h"
//#include "WorldObject.h"
#include "skinned_mesh.h"
#include "skinning_technique.h"
#include "basic_lighting.h"
#include "Engine.h"

//TODO
//	add some constructors
//	first shoot at point
// later missile should have struct(or even class) to check collision, lifetime etc.

class Tower				//: public WorldObject
{
public:
	Tower();
	~Tower();


	Tower(BasicLightingTechnique* light, SkinningTechnique* m_pEffect, Vector3f position, Terrain* ter);

	SkinnedMesh Model3D;
	Mesh Missile;
	float missileLife;
	double Range;
	Vector3f missilePos;
	Vector3f towerPos;
	double distance_to_target;
	double towerHeight;			//only good when scale is 5
	double towerScale;

	BasicLightingTechnique* light;
	SkinningTechnique* m_pEffect;
	Terrain* terrain;



	void Shoot(Pipeline * p, float x, float y, float z);

	void CalcAnimation();

	void LoadModel(string filename);

	void LoadMissile(string filename);

	void Render(Pipeline *p);

	bool IsInRange(Vector3f enemyPos);

private:

	void LimitTowerPosition();


};













#endif