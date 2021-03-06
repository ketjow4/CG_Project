#pragma once
#include <string>
using namespace std;

class Renderable
{
public:
	virtual ~Renderable(){};
	/**
	* Funkcja wyświetlająca obiekt.
	*/
	virtual void Render() = 0;
	/**
	* Funkcja ładująca model z pliku.
	* @param filename nazwa pliku z opisem modelu
	*/
	virtual bool LoadMesh(const string &filename) = 0;
};

