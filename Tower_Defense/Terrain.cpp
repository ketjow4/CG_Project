#include "Terrain.h"

Terrain::Terrain()
{
}


Terrain::~Terrain()
{
	for (int i = 0; i < this->width; ++i)
		delete this->vertices[i];
	delete this->vertices;
	glDeleteLists(this->terrainList, 1);
}

void Terrain::LoadHeightMap(char *filename)
{
	FILE *file = fopen(filename, "rb");
	if (!file) { printf("terrain file error\n"); return; }

	// Get terrain width
	fseek(file, 18, SEEK_SET);
	fread(&this->width, 4, 1, file);

	// Get terrain height
	fseek(file, 22, SEEK_SET);
	fread(&this->height, 4, 1, file);

	// Get terrain data
	int terrainSize = this->width * this->height * 3;
	unsigned char *terrainData = new unsigned char[terrainSize];
	fseek(file, 54, SEEK_SET);
	fread(terrainData, 1, terrainSize, file);
	fclose(file);

	// Init vertices
	this->vertices = new Vector3f*[this->width];
	for (int i = 0; i < this->width; ++i)
		this->vertices[i] = new Vector3f[this->height];

	// Set vertices
	for (int j = 0, tdI = 0; j < this->height; ++j)
	{
		for (int i = 0; i < this->width; ++i, tdI += 3)
		{
			this->vertices[i][j].x = (float)(i);
			this->vertices[i][j].z = (float)(j);
			this->vertices[i][j].y = (float)terrainData[tdI] + (float)terrainData[tdI + 1] + (float)terrainData[tdI + 2];
			this->vertices[i][j].y *= heightFactor / 3.0f;
		}
	}
	delete terrainData;
}

bool Terrain::IsTriangle2dCollision(float x, float z, const Triangle& triangle)
{
	for (int i = 0; i < 3; ++i)
	{
		float v1x = triangle.vertices[(i + 1) % 3].x - triangle.vertices[i].x;
		float v1z = triangle.vertices[(i + 1) % 3].z - triangle.vertices[i].z;
		float v2x = x - triangle.vertices[i].x;
		float v2z = z - triangle.vertices[i].z;
		if (v1z*v2x - v1x*v2z < 0.0f)
			return false;
	}
	return true;
}

Terrain::Triangle Terrain::GetActiveTriangle(float x, float z)
{
	Triangle result;
	int ix1 = abs(ceil(x - 1.0f));
	int ix2 = abs(ceilf(x));
	int iz1 = abs(ceil(z - 1.0f));
	int iz2 = abs(ceilf(z));

	// Check the first of two closest triangles
	result.vertices[0] = this->vertices[ix1][iz1];
	result.vertices[1] = this->vertices[ix1][iz2];
	result.vertices[2] = this->vertices[ix2][iz2];
	if (IsTriangle2dCollision(x, z, result))
		return result;

	// Check the latter one
	result.vertices[0] = this->vertices[ix1][iz1];
	result.vertices[1] = this->vertices[ix2][iz2];
	result.vertices[2] = this->vertices[ix2][iz1];
	if (IsTriangle2dCollision(x, z, result))
		return result;

	// Error
	puts("Terrain::GetActiveTriangle error");
	return Triangle();
}

Vector3f Terrain::GetNormal(const Triangle& triangle)
{
	Vector3f v1, v2;
	v1.x = triangle.vertices[0].x - triangle.vertices[1].x;
	v1.y = triangle.vertices[0].y - triangle.vertices[1].y;
	v1.z = triangle.vertices[0].z - triangle.vertices[1].z;
	v2.x = triangle.vertices[0].x - triangle.vertices[2].x;
	v2.y = triangle.vertices[0].y - triangle.vertices[2].y;
	v2.z = triangle.vertices[0].z - triangle.vertices[2].z;
	Vector3f result = Vector3f((v1.y*v2.z - v1.z*v2.y), (v1.z*v2.x - v1.x*v2.z), (v1.x*v2.y - v1.y*v2.x));
	return result.Normalize();
}

void Terrain::Init(char *filename, float heightFactor)
{
	this->heightFactor = heightFactor;
	this->LoadHeightMap(filename);
	glEnable(GL_TEXTURE_2D);

	float texCoordS = 0.0;
	float texCoordSStep = 1.0 / (float)this->width;
	float texCoordTStep = 1.0 / (float)this->height;

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;

	unsigned int index = 0;
	for (int i = 1; i < this->width; ++i)
	{
		float texCoordT = 0.0;
		for (int j = 1; j < this->height; ++j)
		{
			Triangle triangle;
			triangle.vertices[0] = Vector3f(vertices[i - 1][j - 1].x, vertices[i - 1][j - 1].y, vertices[i - 1][j - 1].z);
			triangle.vertices[1] = Vector3f(vertices[i][j - 1].x, vertices[i][j - 1].y, vertices[i][j - 1].z);
			triangle.vertices[2] = Vector3f(vertices[i][j].x, vertices[i][j].y, vertices[i][j].z);
			Vector3f triangleNormal = GetNormal(triangle);

			Vertex t1BottomLeft
				(
				Vector3f( vertices[i - 1][j - 1].x, vertices[i - 1][j - 1].y, vertices[i - 1][j - 1].z ),
				Vector2f( texCoordS, texCoordT ),
				//triangleNormal//Vector3f(0.0, 0.0, -1.0)
				Vector3f(0.0, 0.0, -1.0)
				);
			Vertices.push_back(t1BottomLeft);
			AddThreeIndices(Indices, index);

			Vertex t1UpperLeft
				(
				Vector3f(vertices[i][j - 1].x, vertices[i][j - 1].y, vertices[i][j - 1].z),
				Vector2f(texCoordS + texCoordSStep, texCoordT),
				//triangleNormal//Vector3f(0.0, 0.0, -1.0)
				Vector3f(0.0, 0.0, -1.0)
				);
			Vertices.push_back(t1UpperLeft);
			AddThreeIndices(Indices, index);

			Vertex t1UpperRight
				(
				Vector3f(vertices[i][j].x, vertices[i][j].y, vertices[i][j].z),
				Vector2f(texCoordS + texCoordSStep, texCoordT + texCoordTStep),
				//triangleNormal//Vector3f(0.0, 0.0, -1.0)
				Vector3f(0.0, 0.0, -1.0)
				);
			Vertices.push_back(t1UpperRight);
			AddThreeIndices(Indices, index);

			Vertex t2BottomLeft
				(
				Vector3f(vertices[i - 1][j - 1].x, vertices[i - 1][j - 1].y, vertices[i - 1][j - 1].z),
				Vector2f(texCoordS, texCoordT),
				//triangleNormal//Vector3f(0.0, 0.0, -1.0)
				Vector3f(0.0, 0.0, -1.0)
				);
			Vertices.push_back(t2BottomLeft);
			AddThreeIndices(Indices, index);

			Vertex t2UpperRight
				(
				Vector3f(vertices[i][j].x, vertices[i][j].y, vertices[i][j].z),
				Vector2f(texCoordS + texCoordSStep, texCoordT + texCoordTStep),
				//triangleNormal//Vector3f(0.0, 0.0, -1.0)
				Vector3f(0.0, 0.0, -1.0)
				);
			Vertices.push_back(t2UpperRight);
			AddThreeIndices(Indices, index);

			Vertex t2BottomRight
				(
				Vector3f(vertices[i - 1][j].x, vertices[i - 1][j].y, vertices[i - 1][j].z),
				Vector2f(texCoordS, texCoordT + texCoordTStep),
				//triangleNormal//Vector3f(0.0, 0.0, -1.0)
				Vector3f(0.0, 0.0, -1.0)
				);
			Vertices.push_back(t2BottomRight);
			AddThreeIndices(Indices, index);

			texCoordT += texCoordTStep;
		}
		texCoordS += texCoordSStep;
	}

	m_Entries.resize(1);
	m_Entries[0].Init(Vertices, Indices);
	m_Entries[0].MaterialIndex = 0;

	m_Textures.resize(1);
	m_Textures[0] = NULL;
	m_Textures[0] = new Texture(GL_TEXTURE_2D, "Models/terrain1texture.bmp");

	if (!m_Textures[0]->Load())
	{
		printf("Error loading texture '%s'\n", "Models/terrain1texture.bmp");
		delete m_Textures[0];
		m_Textures[0] = NULL;

	}
	else 
	{
		printf("Loaded texture '%s'\n", "Models/terrain1texture.bmp");
	}

	SetMaxX();
	SetMaxZ();
	SetMinX();
	SetMinZ();
}


float Terrain::GetTerrainHeight(float x, float z)
{
	Triangle activeTriangle = this->GetActiveTriangle(x, z);
	Vector3f planeNormal = this->GetNormal(activeTriangle);
	float a = planeNormal.x;
	float b = planeNormal.y;
	float c = planeNormal.z;
	float d = -(a*activeTriangle.vertices[0].x + b*activeTriangle.vertices[0].y + c*activeTriangle.vertices[0].z);
	float height = -(a*x + c*z + d) / b;
	return height;
}

void Terrain::Render()
{

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for (unsigned int i = 0; i < m_Entries.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

		const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

		if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex])
		{
			m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
		}

		glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void Terrain::AddThreeIndices(std::vector<unsigned int> &indicesVec, unsigned int &firstIndex)
{
	indicesVec.push_back(firstIndex++);
	indicesVec.push_back(firstIndex++);
	indicesVec.push_back(firstIndex++);
}

void Terrain::SetMaxX()
{
	float maxX = vertices[0][0].x;
	for (int i = 0; i < this->width; i++)
		for (int j = 0; j < this->height; j++)
			maxX = max(maxX, vertices[i][j].x);
	MaxX = maxX;
}

void Terrain::SetMaxZ()
{
	float maxZ = vertices[0][0].z;
	for (int i = 0; i < this->width; i++)
		for (int j = 0; j < this->height; j++)
			maxZ = max(maxZ, vertices[i][j].z);
	MaxZ = maxZ;
}

void Terrain::SetMinX()
{
	float minX = vertices[0][0].x;
	for(int  i = 0; i < this->width; i++)
		for(int j = 0; j < this->height; j++)
			minX = min(minX, vertices[i][j].x);
	MinX = minX;
}

void Terrain::SetMinZ()
{
	float minZ = vertices[0][0].z;
	for (int i = 0; i < this->width; i++)
		for (int j = 0; j < this->height; j++)
			minZ = min(minZ, vertices[i][j].z);
	MinZ = minZ;
}