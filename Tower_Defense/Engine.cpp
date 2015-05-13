#include "Engine.h"


long long Engine::m_startTime = 0;

float Engine::GetRunningTime()
{
	float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)m_startTime) / 1000.0f;
	return RunningTime;
}


Engine::Engine()
{
}

Engine::~Engine()
{
}


void Engine::Init()
{
	light = new BasicLightingTechnique();
	if (!light->Init())
	{
		printf("Error initializing the lighting technique\n");
		//return -1;
	}

	m_pEffect = new SkinningTechnique();
	if (!m_pEffect->Init())
	{
		printf("Error initializing the skinning technique\n");
		//return -1;
	}

	m_pickingTexture = new PickingTexture();
	if (!m_pickingTexture->Init(640, 480))
	{
		printf("Error initializing the picking texture\n");
		//return -1;
	}

	m_pickingEffect = new PickingTechnique();
	if (!m_pickingEffect->Init())
	{
		printf("Error initializing the picking technique\n");
		//return -1;
	}
}

BasicLightingTechnique* Engine::light = NULL;		//use this shaders for static objects
SkinningTechnique* Engine::m_pEffect = NULL;
PickingTexture* Engine::m_pickingTexture = NULL;
PickingTechnique* Engine::m_pickingEffect = NULL;