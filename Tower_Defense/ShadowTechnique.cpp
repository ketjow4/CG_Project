#include "ShadowTechnique.h"

ShadowTechnique::ShadowTechnique()
{}

ShadowTechnique::~ShadowTechnique()
{}

void ShadowTechnique::SetWVP(const Matrix4f& WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}

void ShadowTechnique::SetTextureUnit(uint TextureUnit)
{
	glUniform1i(m_textureLocation, TextureUnit);
}
