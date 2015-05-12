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
	std::vector<std::pair<float, float>> pathPoints;
	std::vector<std::pair<float, float>> possibleTowerPoints;
	//Terrain* terrain;

	//Path(Terrain* terrain);
	Path();
	~Path();
	void Init(char *filename);
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
	// Magenta (255,0,255)
	const static RgbPoint towerPoint;
	const static char towerPointChar = 't';
	// Default
	const static char defaultPointChar = '-';

	void LoadPathMap(char *filename);
	void CalculatePathPoints(char **map);
	char RgbToPointChar(const RgbPoint &rgbPoint) const;
};

