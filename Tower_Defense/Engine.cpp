#include "Engine.h"

Engine::Engine()
	: m_startTime(0), simpleModel(0), animatedModel(0), m_pickingEffect(0), m_pickingTexture(0)
{}

Engine::~Engine()
{}

float Engine::GetRunningTime()
{
	float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)m_startTime) / 1000.0f;
	return RunningTime;
}

void Engine::Init()
{
	simpleModel = new SimpleModelTechnique();
	if (!simpleModel->Init())
		printf("Error initializing the simple model technique\n");

	animatedModel = new AnimatedModelTechnique();
	if (!animatedModel->Init())
		printf("Error initializing the animated model technique\n");

	m_pickingTexture = new PickingTexture();
	if (!m_pickingTexture->Init(WINDOW_WIDTH, WINDOW_HEIGHT))
		printf("Error initializing the picking texture\n");

	m_pickingEffect = new PickingTechnique();
	if (!m_pickingEffect->Init())
		printf("Error initializing the picking technique\n");

	m_simpleShadowEffect = new SimpleShadowTechnique();
	if (!m_simpleShadowEffect->Init())
		printf("Error initializing the shadow map technique\n");

	m_animatedShadowEffect = new AnimatedShadowTechnique();
	if (!m_animatedShadowEffect->Init())
		printf("Error initializing the skinned shadow map technique\n");

	m_shadowMapFBO = new ShadowMapFBO();
	if (!m_shadowMapFBO->Init(WINDOW_WIDTH, WINDOW_HEIGHT))
		printf("Error initializing the shadow map buffer\n");
}
