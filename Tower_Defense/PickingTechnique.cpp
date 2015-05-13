#include "PickingTechnique.h"
#include "util.h"

PickingTechnique::PickingTechnique()
{   
}

bool PickingTechnique::Init()
{
    if (!Technique::Init())
        return false;

    if (!AddShader(GL_VERTEX_SHADER, "Shaders/picking.vs"))
        return false;

    if (!AddShader(GL_FRAGMENT_SHADER, "Shaders/picking.fs"))
        return false;
    
    if (!Finalize())
        return false;

    m_WVPLocation = GetUniformLocation("gWVP");

    if (m_WVPLocation == INVALID_UNIFORM_LOCATION)
        return false;

    return true;
}


void PickingTechnique::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);    
}

