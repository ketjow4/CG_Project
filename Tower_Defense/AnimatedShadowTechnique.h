#pragma once

#include <assert.h>
#include "ShadowTechnique.h"

class AnimatedShadowTechnique : public ShadowTechnique
{
public:
	static const uint MAX_BONES = 100;

	AnimatedShadowTechnique();
	~AnimatedShadowTechnique();
	virtual bool Init();
	void SetBoneTransform(uint Index, const Matrix4f& Transform);
private:
	GLuint m_boneLocation[MAX_BONES];
};

