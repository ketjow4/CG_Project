#include "AnimatedShadowTechnique.h"


AnimatedShadowTechnique::AnimatedShadowTechnique()
{}


AnimatedShadowTechnique::~AnimatedShadowTechnique()
{}

bool AnimatedShadowTechnique::Init()
{
	if (!Technique::Init())
		return false;

	if (!AddShader(GL_VERTEX_SHADER, "Shaders/animatedShadow.vs"))
		return false;

	if (!AddShader(GL_FRAGMENT_SHADER, "Shaders/animatedShadow.fs"))
		return false;

	if (!Finalize())
		return false;

	m_WVPLocation = GetUniformLocation("gWVP");
	m_textureLocation = GetUniformLocation("gShadowMap");

	for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_boneLocation); i++) 
	{
		char Name[128];
		memset(Name, 0, sizeof(Name));
		SNPRINTF(Name, sizeof(Name), "gBones[%d]", i);
		m_boneLocation[i] = GetUniformLocation(Name);
	}

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_textureLocation == INVALID_UNIFORM_LOCATION)
		return false;

	return true;
}

void AnimatedShadowTechnique::SetBoneTransform(uint Index, const Matrix4f& Transform)
{
	assert(Index < MAX_BONES);
	glUniformMatrix4fv(m_boneLocation[Index], 1, GL_TRUE, (const GLfloat*)Transform);
}
