#pragma once
#include "Path.h"

#include <map>

class PathsContainer
{
public:
	/**
	* Funkcja ³aduje œcie¿kê z pliku i wi¹¿e j¹ z podanym kluczem.
	* @param key klucz za pomoc¹ którego bêdziemy siê pózniej odwo³ywaæ do œcie¿ki
	* @oaram pathBmp nazwa bitmapy opisuj¹cej œcie¿kê
	*/
	static void LoadPath(int key, const string &pathBmp);
	/**
	* Funckja zwraca œcie¿kê na podstawie klucza
	* @param key klucz, którego wczeœniej u¿yliœmy do za³adowania œcie¿ki
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

