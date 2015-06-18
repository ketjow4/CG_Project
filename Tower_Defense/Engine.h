#pragma once

#include "GameConstsDefinitions.h"
#include "util.h"
#include "SimpleModelTechnique.h"
#include "AnimatedModelTechnique.h"
#include "PickingTechnique.h"
#include "PickingTexture.h"
#include "SimpleShadowTechnique.h"
#include "AnimatedShadowTechnique.h"
#include "ShadowMapFBO.h"

class Engine
{
public:
	float GetRunningTime();
	SimpleModelTechnique* GetSimpleModel() { return simpleModel; }
	AnimatedModelTechnique* GetAnimatedModel() {return animatedModel;}
	PickingTexture* GetPickingTexture() {return m_pickingTexture;}
	PickingTechnique* GetPickingEffect() { return m_pickingEffect;}
	SimpleShadowTechnique* GetSimpleShadow() { return m_simpleShadowEffect; }
	AnimatedShadowTechnique* GetAnimatedShoadow() { return m_animatedShadowEffect; }
	ShadowMapFBO* GetShadowMapFBO() { return m_shadowMapFBO; }

	/**
	* Funkcja zwraca instancjê silnika gry.
	*/
	static Engine* GetEngine()
	{
		static Engine en;
		if (en.simpleModel == NULL)
			en.Init();
		return &en;
	}

private:
	long long m_startTime;
	SimpleModelTechnique* simpleModel;
	AnimatedModelTechnique* animatedModel;
	PickingTexture* m_pickingTexture;
	PickingTechnique* m_pickingEffect;
	SimpleShadowTechnique* m_simpleShadowEffect;
	AnimatedShadowTechnique* m_animatedShadowEffect;
	ShadowMapFBO* m_shadowMapFBO;

	Engine();
	~Engine();
	Engine(const Engine &e) {}
	/**
	* Funkcja inicjalizuje silnik gry.
	*/
	void Init();
};

