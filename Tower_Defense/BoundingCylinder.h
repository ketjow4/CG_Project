#pragma once
#include "math_3d.h"

class BoundingCylinder
{
public:
	/**
	* Tworzy walec o podstawie równoleg³ejdo p³aszczyzny xz.
	* @param c œrodek podstawy walca
	* @param r promieñ walce
	* @param h wysokoœæ walca
	*/
	BoundingCylinder(const Vector3f &c, float r, float h);
	~BoundingCylinder();
	/**
	* Funkcja zmienia po³o¿enie walca.
	* @param trans nowa wartoœæ przemieszczenia œrodka podstawy walca
	*/
	void SetTrans(const Vector3f &trans);
	/**
	* Funkcja sprawdzaj¹ca czy wyst¹pi³¹ kolizja z zadan¹ kul¹.
	* @param sphereCenter œrodek kuli
	* @param sphereRay promieñ kuli
	*/
	bool SphereCollision(const Vector3f &sphereCenter, float sphereRay) const;
private:
	Vector3f c;				// center of the base
	const Vector3f cNoTrans;// center of the base (no translation);
	const float r;			// ray
	const float rr;			// ray squared
	const float h;			// height
};

