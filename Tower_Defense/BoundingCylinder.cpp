#include "BoundingCylinder.h"


BoundingCylinder::BoundingCylinder(const Vector3f &c, float r, float h)
	: cNoTrans(c), r(r), rr(r*r), h(h)
{}

BoundingCylinder::~BoundingCylinder()
{}

void BoundingCylinder::SetTrans(const Vector3f &trans)
{
	c = cNoTrans + trans;
}

bool BoundingCylinder::SphereCollision(const Vector3f &s, float s_r)
{
	float xzDistSquared = pow(s.x-c.x, 2.f) + pow(s.z-c.z, 2.f);
	float s_rr = s.x * s.x;
	if (c.y <= s.y && s.y <= c.y + h)			// cylinder's y level
		return xzDistSquared <= s_rr + rr;
	if (s.y < c.y - s_r || s.y > c.y + h + s_r)	// too low or too high
		return false;
	if (xzDistSquared <= rr)					// center of the sphere is above/below
		return true;
	Vector3f d = Vector3f(s.x - c.x, s.z - c.z, 0.f).Normalize() * r;
	Vector3f edgeP = c + d;	// edge point closest to the sphere
	if (s.y < c.y)
		edgeP.z += h;
	return pow(s.x - edgeP.x, 2.f) + pow(s.y - edgeP.y, 2.f) + pow(s.z - edgeP.z, 2.f) <= s_rr;
}
