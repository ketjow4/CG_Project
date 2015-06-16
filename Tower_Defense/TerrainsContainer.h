#pragma once
#include "Terrain.h"

#include <map>

class TerrainsContainer
{
public:
	/**
	* Funkcja �aduje teren z pliku i wi��e go z podanym kluczem.
	* @param key klucz za pomoc� kt�rego b�dziemy si� p�zniej odwo�ywa� do terenu
	* @param heightMap nazwa bitmapy opisuj�cej kszta�t terenu
	* @param texture nazwa pliku z tekstur� terenu
	* @param heightFactor wsp�czynnik wysoko�ci
	*/
	static void LoadTerrain(int key, const string &heightMap, const string &texture, float heightFactor);
	/**
	* Funckja zwraca teren na podstawie klucza
	* @param key klucz, kt�rego wcze�niej u�yli�my do za�adowania terenu
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

