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
	/** Zasi�g wie�y */
	double Range;
	/** Pozycja wie�y */
	Vector3f towerPos;
	/** Odleg�o�c do celu */
	double distance_to_target;
	/** Wysoko�� wie�y */
	double towerHeight;
	/** Wsp�czynnik skalowania wie�y */
	double towerScale;
	/** Pociski wystrzelone przez wie�� */
	list<Missile> missiles;
	/** Koszt pojedynczej wie�y */
	static int cost;
	/** Pozosta�y czas prze�adowywania */
	int reloading;

	SimpleModelTechnique* simpleModel;
	AnimatedModelTechnique* animatedModel;
	Terrain* terrain;
	SkinnedMesh* model;

	Tower();
	~Tower();
	Tower(SimpleModelTechnique* simpleModel, AnimatedModelTechnique* animatedModel, Vector3f position, Terrain* ter);

	/**
	* Funkcja sprawiaj�ce, �e wie�a wystrzeliwuje pocisk w strone przeciwnika.
	* @param en rozpatrywany przeciwnik
	*/
	void Shoot(Enemy* en);
	/**
	* Funkcja aktualizuj�ca pozycj� pocisk�w, sprawdzaj�ca ewenlutalne kolizje oraz wy�wietlaj�ca je.
	* @param p potok
	* @param enemies wszyscy aktywni przeciwnicy
	*/
	void UpdateMissiles(Pipeline * p, list<Enemy*> *enemies);
	/**
	* Funkcja skraca czas prze�adowywania.
	*/
	void Reload();
	/**
	* Funkcja wi��aca wie�� z modelem na podstawie klucza.
	* @param key klucz identyfikacyjny modelu wie�y
	*/
	void LoadModel(int key);
	/**
	* Funkcja wi��aca wie�e z modelem pocisku na podstawie klucza.
	* @param key klucz identyfikacyjny modelu pocisku
	*/
	void LoadMissile(int key);
	/**
	* Funckja wy�wietlaj�ca wie�e.
	* @param p potok
	* @param cam obiekt kamery
	*/
	void Render(Pipeline *p, Camera* cam);
	/**
	* Funkcja sprawdzaj�ca czy dany przeciwnik jest w zasi�gu strza�u wie�y.
	* @param enemyPos pozycja rozpatrywanego przeciwnika
	*/
	bool IsInRange(Vector3f enemyPos);
	/**
	* Funkcja wy�wietlaj�ca pocisk.
	* @param missile pocisk
	* @param p potok
	*/
	void RenderMissile(Missile *missile, Pipeline *p);
	/**
	* Funkcja obliczaj�ca transformacje ko�ci na potrzeby animacji.
	*/
	void CalcAnimation();
	/**
	* Funkcja obliczaj�ca transformacje ko�ci na potrzeby animacji przy wy�wietlaniu cieni.
	* @param m_SkinnedShadowTechnique obiekt steruj�cy shaderami cieni
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

