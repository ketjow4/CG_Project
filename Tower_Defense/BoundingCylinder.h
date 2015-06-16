#pragma once
#include "math_3d.h"

class BoundingCylinder
{
public:
	/**
	* Tworzy walec o podstawie r�wnoleg�ejdo p�aszczyzny xz.
	* @param c �rodek podstawy walca
	* @param r promie� walce
	* @param h wysoko�� walca
	*/
	BoundingCylinder(const Vector3f &c, float r, float h);
	~BoundingCylinder();
	/**
	* Funkcja zmienia po�o�enie walca.
	* @param trans nowa warto�� przemieszczenia �rodka podstawy walca
	*/
	void SetTrans(const Vector3f &trans);
	/**
	* Funkcja sprawdzaj�ca czy wyst�pi�� kolizja z zadan� kul�.
	* @param sphereCenter �rodek kuli
	* @param sphereRay promie� kuli
	*/
	bool SphereCollision(const Vector3f &sphereCenter, float sphereRay) const;
private:
	Vector3f c;				// center of the base
	const Vector3f cNoTrans;// center of the base (no translation);
	const float r;			// ray
	const float rr;			// ray squared
	const float h;			// height
};

