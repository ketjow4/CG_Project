#pragma once

#include <GL/glew.h>
#include <stdio.h>

#include "types.h"

class ShadowMapFBO
{
public:
	ShadowMapFBO(void);
	~ShadowMapFBO(void);
	/**
	* Funkcja inicjalizuje buffor przeznaczony do generownia cieni.
	* @param WindowWidth szeroko�� okna
	* @param WindowHeight wysoko�� okna
	*/
	bool Init(uint WindowWidth, uint WindowHeight);
	/**
	* Funkcja prze��cza w tryb zapisu do bufora.
	*/
    void BindForWriting();
	/**
	* Funkcja prze��cza w tryb odczytu z bufora
	*/
    void BindForReading(GLenum TextureUnit);
private:
    GLuint m_fbo;
    GLuint m_shadowMap;

	void FreeResources();
};
