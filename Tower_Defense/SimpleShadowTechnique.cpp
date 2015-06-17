#include "SimpleShadowTechnique.h"


SimpleShadowTechnique::SimpleShadowTechnique()
{}

SimpleShadowTechnique::~SimpleShadowTechnique()
{}

bool SimpleShadowTechnique::Init()
{
    if (!Technique::Init())
        return false;

    if (!AddShader(GL_VERTEX_SHADER, "Shaders/simpleShadow.vs"))
        return false;

    if (!AddShader(GL_FRAGMENT_SHADER, "Shaders/simpleShadow.fs"))
        return false;

    if (!Finalize())
        return false;

    m_WVPLocation = GetUniformLocation("gWVP");
    m_textureLocation = GetUniformLocation("gShadowMap");

    if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
        m_textureLocation == INVALID_UNIFORM_LOCATION)
        return false;

    return true;
}
