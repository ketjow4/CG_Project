#pragma once

#include "Model.h"
#include "SkinnedMesh.h"
#include "AnimatedModelTechnique.h"
#include "SkinnedShadowTechnique.h"
#include "SimpleModelTechnique.h"
#include "Engine.h"
#include "Enemy.h"
#include "Missile.h"
#include <list>


class Tower
{
public:
	/** Zasiêg wie¿y */
	double Range;
	/** Pozycja wie¿y */
	Vector3f towerPos;
	/** Odleg³oœc do celu */
	double distance_to_target;
	/** Wysokoœæ wie¿y */
	double towerHeight;
	/** Wspó³czynnik skalowania wie¿y */
	double towerScale;
	/** Pociski wystrzelone przez wie¿ê */
	list<Missile> missiles;
	/** Koszt pojedynczej wie¿y */
	static int cost;
	/** Pozosta³y czas prze³adowywania */
	int reloading;

	SimpleModelTechnique* simpleModel;
	AnimatedModelTechnique* animatedModel;
	Terrain* terrain;
	SkinnedMesh* model;

	Tower();
	~Tower();
	Tower(SimpleModelTechnique* simpleModel, AnimatedModelTechnique* animatedModel, Vector3f position, Terrain* ter);

	/**
	* Funkcja sprawiaj¹ce, ¿e wie¿a wystrzeliwuje pocisk w strone przeciwnika.
	* @param en rozpatrywany przeciwnik
	*/
	void Shoot(Enemy* en);
	/**
	* Funkcja aktualizuj¹ca pozycjê pocisków, sprawdzaj¹ca ewenlutalne kolizje oraz wyœwietlaj¹ca je.
	* @param p potok
	* @param enemies wszyscy aktywni przeciwnicy
	*/
	void UpdateMissiles(Pipeline * p, list<Enemy*> *enemies);
	/**
	* Funkcja skraca czas prze³adowywania.
	*/
	void Reload();
	/**
	* Funkcja wi¹¿aca wie¿ê z modelem na podstawie klucza.
	* @param key klucz identyfikacyjny modelu wie¿y
	*/
	void LoadModel(int key);
	/**
	* Funkcja wi¹¿aca wie¿e z modelem pocisku na podstawie klucza.
	* @param key klucz identyfikacyjny modelu pocisku
	*/
	void LoadMissile(int key);
	/**
	* Funckja wyœwietlaj¹ca wie¿e.
	* @param p potok
	* @param cam obiekt kamery
	*/
	void Render(Pipeline *p, Camera* cam);
	/**
	* Funkcja sprawdzaj¹ca czy dany przeciwnik jest w zasiêgu strza³u wie¿y.
	* @param enemyPos pozycja rozpatrywanego przeciwnika
	*/
	bool IsInRange(Vector3f enemyPos);
	/**
	* Funkcja wyœwietlaj¹ca pocisk.
	* @param missile pocisk
	* @param p potok
	*/
	void RenderMissile(Missile *missile, Pipeline *p);
	/**
	* Funkcja obliczaj¹ca transformacje koœci na potrzeby animacji.
	*/
	void CalcAnimation();
	/**
	* Funkcja obliczaj¹ca transformacje koœci na potrzeby animacji przy wyœwietlaniu cieni.
	* @param m_SkinnedShadowTechnique obiekt steruj¹cy shaderami cieni
	*/
	void CalcAnimation(SkinnedShadowTechnique *m_SkinnedShadowTechnique);
	Vector3f GetPosition()
	{
		return towerPos;
	}
	Vector3f GetScale()
	{
		return Vector3f(towerScale, towerScale, towerScale);
	}
private:
	Mesh *missileModel;
	int missileType;
	
	void UpdateMissile(Pipeline * p, Missile* missile, list<Enemy*> *enemies);
	void LimitTowerPosition();
};

