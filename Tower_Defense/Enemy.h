#pragma once

#include <iostream>
#include <map>

#include "math_3d.h"
#include "Model.h"
#include "SimpleModelTechnique.h"
#include "Path.h"
#include "Terrain.h"
#include "pipeline.h"
#include "ModelsContainer.h"
#include "Player.h"
#include "Camera.h"

class Enemy
{
public:
	/** Za�adowany model przeciwnika */
	Mesh *model;
	/** Pozosta�e punkty �ycia */
	double HP;
	/** Obra�enia po przej�ciu �cie�ki */
	double Attack;
	/** Identyfikator efektu */
	int effectId;
	/** Efekt trucizny */
	struct Poison
	{
		int duration;
		int degenFreq;
	} poison;

	Enemy();
	~Enemy();
	/**
	* Funkcja pobiera model.
	* @param id klucz modelu
	*/
	void LoadModel(int id);
	/**
	* Funkcja przesuwa przeciwnika po �cie�ce i wy�wietla go.
	* @param p potok
	* @param cam kamera
	*/
	void UpdatePosition(Pipeline *p, Camera* cam);
	/**
	* Funckcja pobiera pozycj� modelu.
	*/
	const Vector3f& GetPosition() const;
	/**
	* Funkcja pobiera kierunek, w kt�rym zwr�cony jest przeciwnik.
	*/
	const Vector3f& GetRotation() const;
	/**
	* Funkcja zwraca identyfikator punktu na �cie�ce, w kt�rym znajduje si� przeciwnik.
	*/
	const int& GetPathIndex() const;
	/**
	* Funkcja zwraca identyfikator punktu na �cie�ce, w kt�rym znajdzie si� przeciwnik po podanej liczbie krok�w.
	* @param steps liczba krok�w
	*/
	Vector3f GetFuturePosition(int steps) const;
	/**
	* Funkcja ustawia u�ywany obiekt zarz�dzaj�cy shaderami.
	* @param simpleModel obiekt zarz�dzaj�cy shaderami wy�wietlania obiekt� statycznych
	*/
	void SetSimpleModel(SimpleModelTechnique* simpleModel);
	/**
	* Funkcja ustawia obecnie wczytany teren.
	* @param terrain teren
	*/
	void SetTerrain(Terrain* terrain);
	/**
	* Funkcja ustawia obecnie wczytan� ��ie�k�.
	* @param path �cie�ka
	*/
	void SetPath(Path* path);
private:
	const static float EffectIntensity[2];
	const static Vector4f EffectColor[2];
	Vector3f position;
	Vector3f rotation;
	int pathIndex;
	SimpleModelTechnique* simpleModel;
	Path* path;
	Terrain* terrain;
};
