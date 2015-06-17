#pragma once

#include <assert.h>
#include "ShadowTechnique.h"

class AnimatedShadowTechnique : public ShadowTechnique
{
public:
	static const uint MAX_BONES = 100;

	AnimatedShadowTechnique();
	~AnimatedShadowTechnique();
	/**
	* Funkcja inicjalizuj�ca shadery s�u�ace do wy�wietlania cieni animowanych obiekt�w.
	*/
	virtual bool Init();
	/**
	* Funkcja przekazuj�ca do shader�w transformacje danej ko�ci.
	*/
	void SetBoneTransform(uint Index, const Matrix4f& Transform);
private:
	GLuint m_boneLocation[MAX_BONES];
};

