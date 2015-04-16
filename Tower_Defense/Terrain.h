#pragma once
#include "GL\glew.h"
#include "math_3d.h"
#include "texture.h"

class Terrain
{
public:
	struct Triangle
	{
		Vector3f vertices[3];
	};
private:
	float heightFactor;

	int terrainList;
	int width, height;
	Vector3f **vertices;

	Texture *texture;

	// Loads bitmap and converts it to vertices.
	void LoadHeightMap(char *filename);

	// Checks if P(x,z) is in triangle T((x1,z1),(x2,z2),(x3,z3))
	bool IsTriangle2dCollision(float x, float z,const Triangle& triangle);

	// Returns terrain triangle that line L(x,z) crosses
	Triangle GetActiveTriangle(float x, float z);

	// Calculates normal to plane of triangle
	Vector3f GetNormal(const Triangle& triangle);

	
public:
	Terrain();
	~Terrain();

	// Initializes terrain object basing on bitmap.
	void Init(char *filename, float heightFactor = 1.0);

	// Calculates height of terrain at P(x,z)
	float GetTerrainHeight(float x, float z);

	// Draws terrain
	void Render();
};

