#pragma once
#include "Renderable.h"
#include "Model.h"

#include <map>

class ModelsContainer
{
public:
	/**
	* Funkcja �aduje model z pliku i wi��e go z podanym kluczem.
	* @param key klucz za pomoc� kt�rego b�dziemy si� p�zniej odwo�ywa� do modelu
	* @param mesh obiekt modelu
	* @param filename nazwa pliku z opisem modelu
	*/
	static void LoadMesh(int key, Renderable *mesh, const string &filename);
	/**
	* Funkcja zwraca model na podstawie klucza.
	* @param key klucz, kt�rego wcze�niej u�yli�my do za�adowania modelu
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
