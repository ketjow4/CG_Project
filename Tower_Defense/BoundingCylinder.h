#pragma once
#include "math_3d.h"

class BoundingCylinder
{
public:
	BoundingCylinder(const Vector3f &c, float r, float h);
	~BoundingCylinder();
	void SetTrans(const Vector3f &trans);
	bool SphereCollision(const Vector3f &sphereCenter, float sphereRay) const;
private:
	Vector3f c;				// center of the base
	const Vector3f cNoTrans;// center of the base (no translation);
	const float r;			// ray
	const float rr;			// ray squared
	const float h;			// height
};

