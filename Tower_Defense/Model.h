#ifndef MODEL_H
#define MODEL_H


#include <stdlib.h>
#include <GL\glew.h>
#include <glut.h>

#include <glm/glm.hpp>					//biblioteka pomocnicza zawierajaca operacje na macierzach i wektorach
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <vector>



#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "util.h"
#include "math_3d.h"
#include "texture.h"
#include "Renderable.h"


struct Vertex
{
    Vector3f m_pos;
    Vector2f m_tex;
    Vector3f m_normal;

    Vertex() {}

    Vertex(const Vector3f& pos, const Vector2f& tex, const Vector3f& normal)
    {
        m_pos    = pos;
        m_tex    = tex;
        m_normal = normal;
    }
};

 struct MeshEntry
 {
        MeshEntry();
        ~MeshEntry();

        void Init(const std::vector<Vertex>& Vertices,
                  const std::vector<unsigned int>& Indices);

        GLuint VB;
        GLuint IB;
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };


class Mesh : public Renderable
{
public:
    Mesh();

    ~Mesh();

    bool LoadMesh(const std::string& Filename);

    void Render();

public:
    bool InitFromScene(const aiScene* pScene, const std::string& Filename);
    void InitMesh(unsigned int Index, const aiMesh* paiMesh);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

   

    std::vector<MeshEntry> m_Entries;
    std::vector<Texture*> m_Textures;
};


#endif