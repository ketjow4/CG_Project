#pragma once
#include <string>
using namespace std;

class Renderable
{
public:
	virtual ~Renderable(){};
	/**
	* Funkcja wyœwietlaj¹ca obiekt.
	*/
	virtual void Render() = 0;
	/**
	* Funkcja ³aduj¹ca model z pliku.
	* @param filename nazwa pliku z opisem modelu
	*/
	virtual bool LoadMesh(const string &filename) = 0;
};

