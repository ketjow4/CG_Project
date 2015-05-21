#pragma once

#include <assert.h>
#include "technique.h"
#include "math_3d.h"
#include "util.h"

class SkinnedShadowTechnique : public Technique
{
public:
	static const uint MAX_BONES = 100;

	SkinnedShadowTechnique();
	~SkinnedShadowTechnique();
	virtual bool Init();
	void SetWVP(const Matrix4f& WVP);
	void SetTextureUnit(unsigned int TextureUnit);
	void SetBoneTransform(uint Index, const Matrix4f& Transform);
private:
	GLuint m_WVPLocation;
	GLuint m_textureLocation;
	GLuint m_boneLocation[MAX_BONES];
};

