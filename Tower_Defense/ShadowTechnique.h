#pragma once

#include "Technique.h"
#include "math_3d.h"
#include "util.h"

class ShadowTechnique :	public Technique
{
public:
	ShadowTechnique();
	~ShadowTechnique();
	/**
	* Funkcja przekazuj¹ca do shaderów macierz WVP.
	*/
	void SetWVP(const Matrix4f& WVP);
	/**
	* Funkcja przekazuj¹ca do shaderów znacznik tekstury.
	*/
	void SetTextureUnit(uint TextureUnit);
protected:
	GLuint m_WVPLocation;
	GLuint m_textureLocation;
};

