#include <limits.h>
#include <string.h>

#include "math_3d.h"
#include "util.h"
#include "basic_lighting.h"


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

    return true;
}

void BasicLightingTechnique::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);    
}


void BasicLightingTechnique::SetWorldMatrix(const Matrix4f& WorldInverse)
{
    //glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)WorldInverse.m);
}


void BasicLightingTechnique::SetColorTextureUnit(unsigned int TextureUnit)
{
    //glUniform1i(m_colorTextureLocation, TextureUnit);
}


void BasicLightingTechnique::SetDirectionalLight(const DirectionalLight& Light)
{
    /*glUniform3f(m_dirLightLocation.Color, Light.Color.x, Light.Color.y, Light.Color.z);
    glUniform1f(m_dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
    Vector3f Direction = Light.Direction;
    Direction.Normalize();
    glUniform3f(m_dirLightLocation.Direction, Direction.x, Direction.y, Direction.z);
    glUniform1f(m_dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);*/
}


void BasicLightingTechnique::SetEyeWorldPos(const Vector3f& EyeWorldPos)
{
    glUniform3f(m_eyeWorldPosLocation, EyeWorldPos.x, EyeWorldPos.y, EyeWorldPos.z);
}


void BasicLightingTechnique::SetMatSpecularIntensity(float Intensity)
{
    //glUniform1f(m_matSpecularIntensityLocation, Intensity);
}


void BasicLightingTechnique::SetMatSpecularPower(float Power)
{
   // glUniform1f(m_matSpecularPowerLocation, Power);
}


void BasicLightingTechnique::SetPointLights(unsigned int NumLights, const PointLight* pLights)
{
   /* glUniform1i(m_numPointLightsLocation, NumLights);
    
    for (unsigned int i = 0 ; i < NumLights ; i++) {
        glUniform3f(m_pointLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
        glUniform1f(m_pointLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
        glUniform1f(m_pointLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
        glUniform3f(m_pointLightsLocation[i].Position, pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
        glUniform1f(m_pointLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
        glUniform1f(m_pointLightsLocation[i].Atten.Linear, pLights[i].Attenuation.Linear);
        glUniform1f(m_pointLightsLocation[i].Atten.Exp, pLights[i].Attenuation.Exp);
    }*/
}

void BasicLightingTechnique::SetSpotLights(unsigned int NumLights, const SpotLight* pLights)
{
   /* glUniform1i(m_numSpotLightsLocation, NumLights);

    for (unsigned int i = 0 ; i < NumLights ; i++) {
        glUniform3f(m_spotLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
        glUniform1f(m_spotLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
        glUniform1f(m_spotLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
        glUniform3f(m_spotLightsLocation[i].Position,  pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
        Vector3f Direction = pLights[i].Direction;
        Direction.Normalize();
        glUniform3f(m_spotLightsLocation[i].Direction, Direction.x, Direction.y, Direction.z);
        glUniform1f(m_spotLightsLocation[i].Cutoff, cosf(ToRadian(pLights[i].Cutoff)));
        glUniform1f(m_spotLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
        glUniform1f(m_spotLightsLocation[i].Atten.Linear,   pLights[i].Attenuation.Linear);
        glUniform1f(m_spotLightsLocation[i].Atten.Exp,      pLights[i].Attenuation.Exp);
    }*/
}
