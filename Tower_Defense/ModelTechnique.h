#pragma once

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


struct SpotLight : public PointLight
{
	Vector3f Direction;
	float Cutoff;

	SpotLight()
	{
		Direction = Vector3f(0.0f, 0.0f, 0.0f);
		Cutoff = 0.0f;
	}
};

class ModelTechnique : public Technique
{
public:
	static const uint MAX_POINT_LIGHTS = 2;
	static const uint MAX_SPOT_LIGHTS = 2;

	ModelTechnique();
	~ModelTechnique();

	/**
	* Funkcja przekazuj�ca do shader�w macierz WVP.
	*/
	void SetWVP(const Matrix4f& WVP);
	/**
	* Funkcja przekazuj�ca do shader�w macierz WV.
	*/
	void SetWV(const Matrix4f& WV);
	/**
	* Funkcja przekazuj�ca do shader�w macierz W.
	*/
	void SetWorldMatrix(const Matrix4f& W);
	/**
	* Funkcja przekazuj�ca do shader�w znacznik tekstury.
	*/
	void SetColorTextureUnit(uint TextureUnit);
	/**
	* Funkcja przekazuj�ca do shader�w �wiat�o kierunkowe.
	*/
	void SetDirectionalLight(const DirectionalLight& Light);
	void SetPointLights(uint NumLights, const PointLight* pLights);
	void SetSpotLights(uint NumLights, const SpotLight* pLights);
	/**
	* Funkcja przekazuj�ca do shader�w pozycj� obserwatora.
	*/
	void SetEyeWorldPos(const Vector3f& EyeWorldPos);
	/**
	* Funkcja przekazuj�ca do shader�w intensywno�� �wiat�a.
	*/
	void SetMatSpecularIntensity(float Intensity);
	/**
	* Funkcja przekazuj�ca do shader�w moc o�wietlenia.
	*/
	void SetMatSpecularPower(float Power);
	/**
	* Funkcja przekazuj�ca do shader�w macierz WVP �wiat�a.
	*/
	void SetLightWVP(const Matrix4f& LightWVP);
	/**
	* Funkcja przekazuj�ca do shader�w kolor mg�y.
	*/
	void SetFogColor(const Vector4f& color);
	/**
	* Funkcja przekazuj�ca do shader�w g�sto�� mg�y.
	*/
	void SetFogDensity(float density);
protected:
	GLuint m_WVPLocation;
	GLuint m_WVLocation;
	GLuint m_WorldMatrixLocation;
	GLuint m_colorTextureLocation;
	GLuint m_eyeWorldPosLocation;
	GLuint m_matSpecularIntensityLocation;
	GLuint m_matSpecularPowerLocation;
	GLuint m_numPointLightsLocation;
	GLuint m_numSpotLightsLocation;
	GLuint m_fogDensity, m_fogColor;
	GLuint m_LightWVPLocation;

	struct
	{
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint DiffuseIntensity;
		GLuint Direction;
	} m_dirLightLocation;

	struct
	{
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

	struct
	{
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint DiffuseIntensity;
		GLuint Position;
		GLuint Direction;
		GLuint Cutoff;
		struct
		{
			GLuint Constant;
			GLuint Linear;
			GLuint Exp;
		} Atten;
	} m_spotLightsLocation[MAX_SPOT_LIGHTS];
};


