#pragma once

#include "ModelTechnique.h"
#include "math_3d.h"

class SimpleModelTechnique : public ModelTechnique
{
public:
	SimpleModelTechnique();

	virtual bool Init();

	void SetColorEffect(const Vector4f& color);
	void SetColorEffectIntensity(float intensity);
	void SetShadowMapTextureUnit(uint TextureUnit);
private:

	GLuint m_samplerLocation;
	GLuint m_shadowMapLocation;

	struct
	{
		GLuint Color;
		GLuint EffectIntensity;
	} m_colorEffect;
};
