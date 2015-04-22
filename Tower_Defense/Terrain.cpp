#include "Terrain.h"

#include "Model.h"

Terrain::Terrain()
{
}


Terrain::~Terrain()
{
	for (int i = 0; i < this->width; ++i)
		delete this->vertices[i];
	delete this->vertices;
	glDeleteLists(this->terrainList,1);
}

void Terrain::LoadHeightMap(char *filename)
{
	FILE *file = fopen(filename,"rb");
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

bool Terrain::IsTriangle2dCollision(float x, float z,const Triangle& triangle)
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
	Vector3f result =  Vector3f((v1.y*v2.z - v1.z*v2.y), (v1.z*v2.x - v1.x*v2.z), (v1.x*v2.y - v1.y*v2.x));
	return result.Normalize();
}

void Terrain::Init(char *filename, float heightFactor)
{
	this->heightFactor = heightFactor;
	this->LoadHeightMap(filename);
	glEnable(GL_TEXTURE_2D);
	/*this->texture = new Texture(GL_TEXTURE_2D, "Models/terrain1texture.bmp");
	this->texture->Load();
	this->texture->Bind(GL_TEXTURE0);*/
	//this->terrainList = glGenLists(1);
	//glNewList(this->terrainList, GL_COMPILE);
	//{
		//glColor4f(1.0, 1.0, 1.0, 1.0);
		//glBegin(GL_TRIANGLES);
		//{
			float texCoordS = 0.0;
			float texCoordSStep = 1.0 / (float)this->width;
			float texCoordTStep = 1.0 / (float)this->height;
			
			 std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
			
	  Vertex v(Vector3f(0.0 , -100.0, 0.0),
                 Vector2f(0.0, 0.0),
                 Vector3f(0.0,0.0,-1.0));

        Vertices.push_back(v);

		Indices.push_back(0);
        Indices.push_back(1);
        Indices.push_back(2);


		 Vertex v1(Vector3f(300.0 , 0.0, 0.0),
                 Vector2f(1.0, 0.0),
                 Vector3f(0.0,0.0,-1.0));

        Vertices.push_back(v1);

		Indices.push_back(3);
        Indices.push_back(4);
        Indices.push_back(5);

		 Vertex v2(Vector3f(300.0 , 0.0, 300.0),
                 Vector2f(1.0, 1.0),
                 Vector3f(0.0,0.0,-1.0));

        Vertices.push_back(v2);

		Indices.push_back(6);
        Indices.push_back(7);
        Indices.push_back(8);
    
		m_Entries.resize(1);
    m_Entries[0].Init(Vertices, Indices);
	m_Entries[0].MaterialIndex = 0;

	m_Textures.resize(1);
	 m_Textures[0] = NULL;
	 m_Textures[0] = new Texture(GL_TEXTURE_2D, "Models/terrain1texture.bmp");



	  if (!m_Textures[0]->Load()) {
                    printf("Error loading texture '%s'\n", "Models/terrain1texture.bmp");
                    delete m_Textures[0];
                    m_Textures[0] = NULL;
                   
                }
                else {
                    printf("Loaded texture '%s'\n", "Models/terrain1texture.bmp");
                }
			
		/*	glTexCoord2f(0.0, 0.0);
			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(0.0, -100.0, 0.0);*/
			
			/*glTexCoord2f(1.0, 0.0);
			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(300.0, 0.0, 0.0);*/
			
			/*glTexCoord2f(1.0, 1.0);
			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(300.0, 0.0, 300.0);*/


			//for (int i = 1; i < this->width; ++i)
			//{
			//	float texCoordT = 0.0;
			//	for (int j = 1; j < this->height; ++j)
			//	{

			//		glTexCoord2f(texCoordS, texCoordT); //glTexCoord2f(0.0, 0.0);
			//		glNormal3f(0.0, 0.0, 1.0);
			//		glVertex3f(vertices[i - 1][j - 1].x, vertices[i - 1][j - 1].y, vertices[i - 1][j - 1].z);

			//		glTexCoord2f(texCoordS + texCoordSStep, texCoordT); //glTexCoord2f(1.0, 0.0);
			//		glNormal3f(0.0, 0.0, 1.0);
			//		glVertex3f(vertices[i][j - 1].x, vertices[i][j - 1].y, vertices[i][j - 1].z);
			//		
			//		glTexCoord2f(texCoordS + texCoordSStep, texCoordT + texCoordTStep); //glTexCoord2f(1.0, 1.0);
			//		glNormal3f(0.0, 0.0, 1.0);
			//		glVertex3f(vertices[i][j].x, vertices[i][j].y, vertices[i][j].z);

			//		glTexCoord2f(texCoordS, texCoordT); //glTexCoord2f(0.0, 0.0);
			//		glNormal3f(0.0, 0.0, 1.0);
			//		glVertex3f(vertices[i - 1][j - 1].x, vertices[i - 1][j - 1].y, vertices[i - 1][j - 1].z);

			//		glTexCoord2f(texCoordS + texCoordSStep, texCoordT + texCoordTStep); //glTexCoord2f(1.0, 1.0);
			//		glNormal3f(0.0, 0.0, 1.0);
			//		glVertex3f(vertices[i][j].x, vertices[i][j].y, vertices[i][j].z);

			//		glTexCoord2f(texCoordS, texCoordT + texCoordTStep); //glTexCoord2f(0.0, 1.0);
			//		glNormal3f(0.0, 0.0, 1.0);
			//		glVertex3f(vertices[i - 1][j].x, vertices[i - 1][j].y, vertices[i - 1][j].z);

			//		texCoordT += texCoordTStep;

			//		//printf("%f ; %f\n", texCoordX, texCoordY);
			//	}
			//	texCoordS += texCoordSStep;
			//}
		//}
		//glEnd();
	//}
	//glEndList();
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
	/*this->texture->Bind(GL_TEXTURE0);
	glCallList(this->terrainList);*/

	 glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for (unsigned int i = 0 ; i < m_Entries.size() ; i++) {
        glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

        const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

        if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) {
            m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
        }
		
        glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES,0,m_Entries[i].NumIndices);
    }
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}