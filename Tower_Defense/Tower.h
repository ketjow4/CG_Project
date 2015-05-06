#ifndef TOWER_H
#define TOWER_H

#include "Model.h"
//#include "WorldObject.h"
#include "skinned_mesh.h"

//TODO
//	add some constructors
//	first shoot at point
// later missile should have struct(or even class) to check collision, lifetime etc.

class Tower				//: public WorldObject
{
public:
	Tower();
	~Tower();


	SkinnedMesh Model3D;
	Mesh Missile;
	float missileLife;
	double Range;
	Vector3f missilePos;


	void Shoot();


	void LoadModel(string filename);

	void LoadMissile(string filename);

	void Render();

private:



};













#endif