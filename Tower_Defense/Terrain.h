#pragma once
#include "GL\glew.h"
#include "math_3d.h"
#include "texture.h"
#include "Model.h"

class Terrain
{
public:
	/** Maksymalna wsp�rz�dna x terenu */
	float MaxX;
	/** Maksymalna wsp�rz�dna z terenu */
	float MaxZ;
	/** Minimalna wsp�rz�dna x terenu */
	float MinX;
	/** Minimalna wsp�rz�dna z terenu */
	float MinZ;

	Terrain();
	~Terrain();
	/**
	* Inicjalizuje teren na podstawie mapy wysoko�ci.
	* @param heightMap nazwa bitmapy opisuj�cej kszta�t terenu
	* @param texture nazwa pliku z tekstur� terenu
	* @param heightFactor wsp�czynnik wysoko�ci
	*/
	void Init(const string &heightMap, const string &texture, float heightFactor = 1.0);
	/**
	* Funkcja oblicza wysoko�� y w punkcie (x,z)
	* @param x wsp�rz�dna x w �wiecie gry
	* @param z wsp�rz�dna z w �wiecie gry
	*/
	float GetTerrainHeight(float x, float z);
	/**
	* Funkcja wy�wietlaj�ca teren.
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

