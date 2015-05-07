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
