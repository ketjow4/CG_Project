#ifndef TOWER_H
#define TOWER_H

#include "Model.h"

//TODO
//	add some constructors
//	first shoot at point
// later missile should have struct(or even class) to check collision, lifetime etc.

class Tower
{
public:
	Tower();
	~Tower();


	Vector3f WorldPosition;
	Mesh Model3D;
	Mesh Missile;
	double Range;

	void Shoot();

	void SetPosition(Vector3f position);

	void LoadModel(string filename);

	void LoadMissile(string filename);

private:



};













#endif