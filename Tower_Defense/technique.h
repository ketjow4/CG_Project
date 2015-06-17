#pragma once

#include <list>
#include <GL/glew.h>

class Technique
{
public:

    Technique();
    virtual ~Technique();
	/**
	* Funkcja inicjalizuj�ca shadery.
	*/
    virtual bool Init();
	/**
	* Funkcja prze��cza na dan� grup� shader�w.
	*/
    void Enable();

protected:
	GLuint m_shaderProg;

	/**
	* Funckja inicjalizuje shared z pliku. Zwraca true w przypadku sukcesu.
	* @param ShaderType rodzaj shadera
	* @param pFilename nazwa pliku z shaderem
	*/
    bool AddShader(GLenum ShaderType, const char* pFilename);
	/**
	* Funkcja ko�cz�ca proces inicjalizacji shader�w. Zwraca true w przypadku sukcesu.
	*/
    bool Finalize();
	/**
	* Funckja zwraca identyfikator zmiennej uniform.
	* @param pUniformName nazwa szukanej zmiennej
	*/
    GLint GetUniformLocation(const char* pUniformName);
private:
    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;
};

