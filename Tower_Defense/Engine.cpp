#include "Engine.h"

long long Engine::m_startTime = 0;

Engine::Engine()
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
	if (!m_pickingTexture->Init(640, 480))
		printf("Error initializing the picking texture\n");

	m_pickingEffect = new PickingTechnique();
	if (!m_pickingEffect->Init())
		printf("Error initializing the picking technique\n");
}

SimpleModelTechnique* Engine::simpleModel = NULL;
AnimatedModelTechnique* Engine::animatedModel = NULL;
PickingTexture* Engine::m_pickingTexture = NULL;
PickingTechnique* Engine::m_pickingEffect = NULL;