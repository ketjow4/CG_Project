#pragma once
#include "GL\glew.h"
#include "math_3d.h"
#include "texture.h"
#include "Model.h"

class Terrain
{
public:
	/** Maksymalna wspó³rzêdna x terenu */
	float MaxX;
	/** Maksymalna wspó³rzêdna z terenu */
	float MaxZ;
	/** Minimalna wspó³rzêdna x terenu */
	float MinX;
	/** Minimalna wspó³rzêdna z terenu */
	float MinZ;

	Terrain();
	~Terrain();
	/**
	* Inicjalizuje teren na podstawie mapy wysokoœci.
	* @param heightMap nazwa bitmapy opisuj¹cej kszta³t terenu
	* @param texture nazwa pliku z tekstur¹ terenu
	* @param heightFactor wspó³czynnik wysokoœci
	*/
	void Init(const string &heightMap, const string &texture, float heightFactor = 1.0);
	/**
	* Funkcja oblicza wysokoœæ y w punkcie (x,z)
	* @param x wspó³rzêdna x w œwiecie gry
	* @param z wspó³rzêdna z w œwiecie gry
	*/
	float GetTerrainHeight(float x, float z);
	/**
	* Funkcja wyœwietlaj¹ca teren.
	*/
	void Render();
private:
	std::vector<MeshEntry> m_Entries;
	std::vector<Texture*> m_Textures;
	float heightFactor;
	int terrainList;
	int width, height;
	Vector3f **vertices;
	Texture *texture;

	struct Triangle
	{
		Vector3f vertices[3];
	};

	// Loads bitmap and converts it to vertices.
	void LoadHeightMap(const string &filename);
	// Checks if P(x,z) is in triangle T((x1,z1),(x2,z2),(x3,z3))
	bool IsTriangle2dCollision(float x, float z,const Triangle& triangle);
	// Returns terrain triangle that line L(x,z) crosses
	Triangle GetActiveTriangle(float x, float z);
	// Calculates normal to plane of triangle
	Vector3f GetNormal(const Triangle& triangle);
	void AddThreeIndices(std::vector<unsigned int> &indicesVec, unsigned int &firstIndex);

	void SetMaxX();
	void SetMaxZ();
	void SetMinX();
	void SetMinZ();
};

