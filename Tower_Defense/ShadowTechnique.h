#pragma once

#include "Technique.h"
#include "math_3d.h"
#include "util.h"

class ShadowTechnique :	public Technique
{
public:
	ShadowTechnique();
	~ShadowTechnique();
	void SetWVP(const Matrix4f& WVP);
	void SetTextureUnit(unsigned int TextureUnit);
protected:
	GLuint m_WVPLocation;
	GLuint m_textureLocation;
};

