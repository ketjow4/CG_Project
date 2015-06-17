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
	/** Za³adowany model przeciwnika */
	Mesh *model;
	/** Pozosta³e punkty ¿ycia */
	double HP;
	/** Obra¿enia po przejœciu œcie¿ki */
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
	* Funkcja przesuwa przeciwnika po œcie¿ce i wyœwietla go.
	* @param p potok
	* @param cam kamera
	*/
	void UpdatePosition(Pipeline *p, Camera* cam);
	/**
	* Funckcja pobiera pozycjê modelu.
	*/
	const Vector3f& GetPosition() const;
	/**
	* Funkcja pobiera kierunek, w którym zwrócony jest przeciwnik.
	*/
	const Vector3f& GetRotation() const;
	/**
	* Funkcja zwraca identyfikator punktu na œcie¿ce, w którym znajduje siê przeciwnik.
	*/
	const int& GetPathIndex() const;
	/**
	* Funkcja zwraca identyfikator punktu na œcie¿ce, w którym znajdzie siê przeciwnik po podanej liczbie kroków.
	* @param steps liczba kroków
	*/
	Vector3f GetFuturePosition(int steps) const;
	/**
	* Funkcja ustawia u¿ywany obiekt zarz¹dzaj¹cy shaderami.
	* @param simpleModel obiekt zarz¹dzaj¹cy shaderami wyœwietlania obiektó statycznych
	*/
	void SetSimpleModel(SimpleModelTechnique* simpleModel);
	/**
	* Funkcja ustawia obecnie wczytany teren.
	* @param terrain teren
	*/
	void SetTerrain(Terrain* terrain);
	/**
	* Funkcja ustawia obecnie wczytan¹ œæie¿kê.
	* @param path œcie¿ka
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
