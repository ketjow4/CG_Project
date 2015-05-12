#include "Missile.h"

Missile::Missile(const Vector3f &pos, const Vector3f &dir, float speed, int lifetime)
	: pos(pos), dir(dir), speed(speed), lifetime(lifetime)
{}

Missile::~Missile()
{}

void Missile::UpdateMissile()
{
	pos += dir * speed;
	--lifetime;
}

bool Missile::Collide(Enemy *enemy) const
{
	Vector3f enemyPos = enemy->GetPosition();
	if (sqrt
		(
			pow(enemyPos.x - pos.x, 2.0) +
			pow(enemyPos.y - pos.y, 2.0) +
			pow(enemyPos.z - pos.z, 2.0)
		) < 10.f)
	{
		return true;
	}
	return false;
}

bool Missile::Collide(Terrain *terrain) const
{
	if (pos.x < terrain->MinX || terrain->MaxX < pos.x ||
		pos.z < terrain->MinZ || terrain->MaxZ < pos.z)
		return true;
	float terrainY = terrain->GetTerrainHeight(pos.x, pos.z);
	if (pos.y <= terrainY)
		return true;
	return false;
}
