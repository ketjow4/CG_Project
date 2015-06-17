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
	* Funkcja inicjalizuj¹ca shadery s³u¿ace do wyœwietlania cieni animowanych obiektów.
	*/
	virtual bool Init();
	/**
	* Funkcja przekazuj¹ca do shaderów transformacje danej koœci.
	*/
	void SetBoneTransform(uint Index, const Matrix4f& Transform);
private:
	GLuint m_boneLocation[MAX_BONES];
};

