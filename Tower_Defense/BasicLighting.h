#ifndef LIGHTING_TECHNIQUE_H
#define	LIGHTING_TECHNIQUE_H

#include "technique.h"
#include "math_3d.h"



struct BaseLight
{
    Vector3f Color;
    float AmbientIntensity;
    float DiffuseIntensity;

    BaseLight()
    {
        Color = Vector3f(0.0f, 0.0f, 0.0f);
        AmbientIntensity = 0.0f;
        DiffuseIntensity = 0.0f;
    }
};

struct DirectionalLight : public BaseLight
{        
    Vector3f Direction;

    DirectionalLight()
    {
        Direction = Vector3f(0.0f, 0.0f, 0.0f);
    }
};

struct PointLight : public BaseLight
{
    Vector3f Position;

    struct
    {
        float Constant;
        float Linear;
        float Exp;
    } Attenuation;

    PointLight()
    {
        Position = Vector3f(0.0f, 0.0f, 0.0f);
        Attenuation.Constant = 1.0f;
        Attenuation.Linear = 0.0f;
        Attenuation.Exp = 0.0f;
    }
};


class BasicLightingTechnique : public Technique {
public:
	static const unsigned int MAX_POINT_LIGHTS = 10;

    BasicLightingTechnique();

    virtual bool Init();

    void SetWVP(const Matrix4f& WVP);
	void SetWorldMatrix(const Matrix4f& WVP);
	void SetTextureUnit(unsigned int TextureUnit);
    void SetDirectionalLight(const DirectionalLight& Light);
	void SetEyeWorldPos(const Vector3f& EyeWorldPos);
    void SetMatSpecularIntensity(float Intensity);
    void SetMatSpecularPower(float Power);		//TODO change in future to get power from model material
	void SetPointLights(unsigned int NumLights, const PointLight* pLights);

	void SetColorEffect(const Vector4f& color);
	void SetColorEffectIntensity(float intensity);
private:

    GLuint m_WVPLocation;
    GLuint m_samplerLocation;
    GLuint m_WorldMatrixLocation;
	GLuint m_eyeWorldPosLocation;
    GLuint m_matSpecularIntensityLocation;
    GLuint m_matSpecularPowerLocation;
	GLuint m_numPointLightsLocation;
	
	struct {
		GLuint Color;
		GLuint EffectIntensity;
	} m_colorEffect;

	struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Direction;
    } m_dirLightLocation;

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        struct
        {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } m_pointLightsLocation[MAX_POINT_LIGHTS];
};


#endif	/* LIGHTING_TECHNIQUE_H */
