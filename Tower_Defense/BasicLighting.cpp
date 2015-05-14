#include <limits.h>
#include <string.h>

#include "math_3d.h"
#include "util.h"
#include "BasicLighting.h"


BasicLightingTechnique::BasicLightingTechnique()
{   
}

bool BasicLightingTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "Shaders/basic_lighting.vs")) {
        return false;
    }


    if (!AddShader(GL_FRAGMENT_SHADER, "Shaders/basic_lighting.fs")) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

    m_WVPLocation = GetUniformLocation("gWVP");
	m_WorldMatrixLocation = GetUniformLocation("gWorld");
    m_samplerLocation = GetUniformLocation("gSampler");
    m_dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Color");
    m_dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.AmbientIntensity");
    m_dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
    m_dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.DiffuseIntensity");
	m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
    m_matSpecularPowerLocation = GetUniformLocation("gSpecularPower");

    return true;
}

void BasicLightingTechnique::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);    
}

void BasicLightingTechnique::SetWorldMatrix(const Matrix4f& WorldInverse)
{
    glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)WorldInverse.m);
}

void BasicLightingTechnique::SetTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(m_samplerLocation, TextureUnit);
}


void BasicLightingTechnique::SetDirectionalLight(const DirectionalLight& Light)
{
    glUniform3f(m_dirLightLocation.Color, Light.Color.x, Light.Color.y, Light.Color.z);
    glUniform1f(m_dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
    Vector3f Direction = Light.Direction;
    Direction.Normalize();
    glUniform3f(m_dirLightLocation.Direction, Direction.x, Direction.y, Direction.z);
    glUniform1f(m_dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
}

void BasicLightingTechnique::SetEyeWorldPos(const Vector3f& EyeWorldPos)
{
    glUniform3f(m_eyeWorldPosLocation, EyeWorldPos.x, EyeWorldPos.y, EyeWorldPos.z);
}

void BasicLightingTechnique::SetMatSpecularIntensity(float Intensity)
{
    glUniform1f(m_matSpecularIntensityLocation, Intensity);
}

void BasicLightingTechnique::SetMatSpecularPower(float Power)
{
    glUniform1f(m_matSpecularPowerLocation, Power);
}