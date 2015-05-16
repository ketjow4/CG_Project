#pragma once
#include "math_3d.h"

class BoundingCylinder
{
public:
	BoundingCylinder(const Vector3f &c, float r, float h);
	~BoundingCylinder();
	void SetTrans(const Vector3f &trans);
	bool SphereCollision(const Vector3f &sphereCenter, float sphereRay);
private:
	Vector3f c;			// center of the base
	Vector3f cNoTrans;	// center of the base (no translation);
	float r;			// ray
	float rr;			// ray squared
	float h;			// height
};

