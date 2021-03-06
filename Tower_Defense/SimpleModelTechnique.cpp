#include <limits.h>
#include <string.h>

#include "math_3d.h"
#include "util.h"
#include "SimpleModelTechnique.h"


SimpleModelTechnique::SimpleModelTechnique()
{}

bool SimpleModelTechnique::Init()
{
    if (!Technique::Init()) 
	{
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "Shaders/simpleModel.vs")) 
	{
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "Shaders/simpleModel.fs")) 
	{
        return false;
    }

    if (!Finalize()) 
	{
        return false;
    }

    m_WVPLocation = GetUniformLocation("gWVP");
	m_WVLocation = GetUniformLocation("gWV");
    m_WorldMatrixLocation = GetUniformLocation("gWorld");
    m_samplerLocation = GetUniformLocation("gSampler");
    m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
    m_dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Base.Color");
    m_dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
    m_dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
    m_dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
    m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
    m_matSpecularPowerLocation = GetUniformLocation("gSpecularPower");
    m_numPointLightsLocation = GetUniformLocation("gNumPointLights");
	m_colorEffect.Color = GetUniformLocation("gColorEffect.Color");
	m_colorEffect.EffectIntensity = GetUniformLocation("gColorEffect.EffectIntensity");
	m_numSpotLightsLocation = GetUniformLocation("gNumSpotLights");
	m_shadowMapLocation = GetUniformLocation("gShadowMap");
	m_LightWVPLocation = GetUniformLocation("gLightWVP");
	m_fogDensity = GetUniformLocation("fogDensity");
	m_fogColor = GetUniformLocation("fogColor");

	 for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_pointLightsLocation) ; i++) 
	 {
        char Name[128];
        memset(Name, 0, sizeof(Name));
        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.Color", i);
        m_pointLightsLocation[i].Color = GetUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.AmbientIntensity", i);
        m_pointLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Position", i);
        m_pointLightsLocation[i].Position = GetUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.DiffuseIntensity", i);
        m_pointLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Constant", i);
        m_pointLightsLocation[i].Atten.Constant = GetUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Linear", i);
        m_pointLightsLocation[i].Atten.Linear = GetUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Exp", i);
        m_pointLightsLocation[i].Atten.Exp = GetUniformLocation(Name);
	}

	 for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_spotLightsLocation) ; i++) 
	 {
		 char Name[128];
		 memset(Name, 0, sizeof(Name));
		 SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.Color", i);
		 m_spotLightsLocation[i].Color = GetUniformLocation(Name);

		 SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.AmbientIntensity", i);
		 m_spotLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);

		 SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Position", i);
		 m_spotLightsLocation[i].Position = GetUniformLocation(Name);

		 SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Direction", i);
		 m_spotLightsLocation[i].Direction = GetUniformLocation(Name);

		 SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Cutoff", i);
		 m_spotLightsLocation[i].Cutoff = GetUniformLocation(Name);

		 SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.DiffuseIntensity", i);
		 m_spotLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);

		 SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Constant", i);
		 m_spotLightsLocation[i].Atten.Constant = GetUniformLocation(Name);

		 SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Linear", i);
		 m_spotLightsLocation[i].Atten.Linear = GetUniformLocation(Name);

		 SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Exp", i);
		 m_spotLightsLocation[i].Atten.Exp = GetUniformLocation(Name);

	 }

    return true;
}

void SimpleModelTechnique::SetColorEffect(const Vector4f& color)
{
	glUniform4f(m_colorEffect.Color, color.x, color.y, color.z, color.w);
}

void SimpleModelTechnique::SetColorEffectIntensity(float intensity)
{
	glUniform1f(m_colorEffect.EffectIntensity, intensity);
}

void SimpleModelTechnique::SetShadowMapTextureUnit(uint TextureUnit)
{
    glUniform1i(m_shadowMapLocation, TextureUnit);
}
