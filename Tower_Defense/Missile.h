#pragma once
#include "math_3d.h"
#include "Enemy.h"
#include "Terrain.h"

class Missile
{
public:
	Vector3f pos;
	int lifetime;

	Missile(const Vector3f &pos, const Vector3f &dir, float speed, int lifetime);
	~Missile();

	void UpdateMissile();
	bool Collide(Enemy *enemy) const;
	bool Collide(Terrain *terrain) const;
private:
	Vector3f dir;
	float speed;
};

