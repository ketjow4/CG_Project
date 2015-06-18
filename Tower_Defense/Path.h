#pragma once
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include "math_3d.h"
#include "Terrain.h"

class Path
{
public:
	/** Kolejne punktu na �cie�ce */
	vector<pair<float, float>> pathPoints;
	/** Punkty, w kt�rych mo�na postawi� wie�e */
	vector<pair<float, float>> possibleTowerPoints;

	Path();
	~Path();
	/**
	* Funkcja inicjalizuje �cie�k� na podstawie pliku.
	* @param filename plik z opisem �cie�ki
	*/
	void Init(const string &filename);
	/**
	* Funkcja zwraca wektor kierunku obiektu wzgl�dem podanego punktu na �cie�ce.
	* @param currentPos pozycja danego obiektu
	* @param nextPathPointIndex indeks punktu na �cie�ce, w stron� kt�rego zwr�cony jest obiekt
	*/
	Vector3f GetRotation(const Vector3f &currentPos, int nextPathPointIndex) const;
private:
	struct RgbPoint
	{
		unsigned int r, g, b;
		RgbPoint(unsigned int r, unsigned int g, unsigned int b)
			: r(r), g(g), b(b)
		{}
		bool operator == (const RgbPoint &other) const
		{
			return r == other.r && g == other.g && b == other.b;
		}
	};

	int width, height;

	// Black (0,0,0)
	const static RgbPoint pathPoint;
	const static char pathPointChar = 'p';
	// Blue (0,0,255)
	const static RgbPoint beginPoint;
	const static char beginPointChar = 'b';
	// Red (255,0,0)
	const static RgbPoint endPoint;
	const static char endPointChar = 'e';
	// Magenta (255,0,255) / Yellow (255,255,0)
	const static RgbPoint towerPoint, alternativeTowerPoint;
	const static char towerPointChar = 't';
	// Default
	const static char defaultPointChar = '-';

	void SmoothPath();
	void LoadPathMap(const string &filename);
	void CalculatePathPoints(char **map);
	char RgbToPointChar(const RgbPoint &rgbPoint) const;
};

