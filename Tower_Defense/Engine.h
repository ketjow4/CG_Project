#ifndef ENGINE_H
#define ENGINE_H

#include "util.h"
#include "SimpleModelTechnique.h"
#include "AnimatedModelTechnique.h"
#include "PickingTechnique.h"
#include "PickingTexture.h"


class Engine
{
public:
	Engine();
	~Engine();

	Engine(const Engine &e) {}


	static long long m_startTime;


	static float GetRunningTime();

	static SimpleModelTechnique* simpleModel;		//use this shaders for static objects
	static AnimatedModelTechnique* animatedModel;
	static PickingTexture* m_pickingTexture;
	static PickingTechnique* m_pickingEffect;

	

	SimpleModelTechnique* GetSimpleModel() { return simpleModel; }
	AnimatedModelTechnique* GetAnimatedModel() {return animatedModel;}
	PickingTexture* GetpickingTexture() {return m_pickingTexture;}
	PickingTechnique* GetpickingEffect() { return m_pickingEffect;}

	//use only this to get something from engine
	static Engine GetEngine()
	{
		static Engine en;
		if (en.simpleModel == NULL)
		{
			Init();
		}
		return en;
	}

private:
	static void Init();
};





#endif