#pragma once
#include "Path.h"

#include <map>

class PathsContainer
{
public:
	/**
	* Funkcja �aduje �cie�k� z pliku i wi��e j� z podanym kluczem.
	* @param key klucz za pomoc� kt�rego b�dziemy si� p�zniej odwo�ywa� do �cie�ki
	* @oaram pathBmp nazwa bitmapy opisuj�cej �cie�k�
	*/
	static void LoadPath(int key, const string &pathBmp);
	/**
	* Funckja zwraca �cie�k� na podstawie klucza
	* @param key klucz, kt�rego wcze�niej u�yli�my do za�adowania �cie�ki
	*/
	static Path* Get(int key);
	/**
	* Funkcja zwalnia wszystkie zasoby.
	*/
	static void FreeResources();
private:
	static map<int, Path*> paths;

	PathsContainer();
	~PathsContainer();
};

