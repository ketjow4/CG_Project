#pragma once
#include "Terrain.h"

#include <map>

class TerrainsContainer
{
public:
	/**
	* Funkcja ³aduje teren z pliku i wi¹¿e go z podanym kluczem.
	* @param key klucz za pomoc¹ którego bêdziemy siê pózniej odwo³ywaæ do terenu
	* @param heightMap nazwa bitmapy opisuj¹cej kszta³t terenu
	* @param texture nazwa pliku z tekstur¹ terenu
	* @param heightFactor wspó³czynnik wysokoœci
	*/
	static void LoadTerrain(int key, const string &heightMap, const string &texture, float heightFactor);
	/**
	* Funckja zwraca teren na podstawie klucza
	* @param key klucz, którego wczeœniej u¿yliœmy do za³adowania terenu
	*/
	static Terrain* Get(int key);
	/**
	* Funkcja zwalnia wszystkie zasoby.
	*/
	static void FreeResources();
private:
	static map<int, Terrain*> terrains;

	TerrainsContainer();
	~TerrainsContainer();
};

