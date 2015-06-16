#pragma once
#include "Renderable.h"
#include "Model.h"

#include <map>

class ModelsContainer
{
public:
	/**
	* Funkcja ³aduje model z pliku i wi¹¿e go z podanym kluczem.
	* @param key klucz za pomoc¹ którego bêdziemy siê pózniej odwo³ywaæ do modelu
	* @param mesh obiekt modelu
	* @param filename nazwa pliku z opisem modelu
	*/
	static void LoadMesh(int key, Renderable *mesh, const string &filename);
	/**
	* Funkcja zwraca model na podstawie klucza.
	* @param key klucz, którego wczeœniej u¿yliœmy do za³adowania modelu
	*/
	static Renderable* Get(int key);
	/**
	* Funkcja zwalnia wszystkie zasoby.
	*/
	static void FreeResources();
private:
	static map<int, Renderable*> models;

	ModelsContainer();
	~ModelsContainer();
};
