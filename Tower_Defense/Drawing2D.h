#pragma once

#include "Technique.h"
#include "math_3d.h"
#include "texture.h"

class Drawing2D : public Technique
{
public:
	Drawing2D(void);
	~Drawing2D(void);

	/**
	* Funkcja inicjalizuj¹ca shadery s³u¿ace do wyœwietlania grafik 2d.
	*/
	virtual bool Init();
	/**
	* Funkcja przekazuj¹ca do shaderów macierz WVP.
	*/
	void SetWVP(const Matrix4f& WVP);
	/**
	* Funkcja rysuje prostok¹t.
	* @param x wspó³rzêdna x pocz¹tku prostok¹ta
	* @param y wspó³rzêdna y pocz¹tku prostok¹ta
	* @param width szerokoœæ prostok¹ta
	* @param height wysokoœæ prostok¹ta
	* @param isTex 1 jeœli chcemy oteksturowaæ prostok¹t
	* @param tex tekstura prostokata
	* @param color kolor prostokat¹
	*/
	void RenderQuad(int x,int y, int width, int height, int isTex, Texture* tex, Vector3f color = Vector3f(1,1,1));
private:
	GLuint VAO,VBO;
	GLuint m_WVPLocation;
	GLuint m_ColorLocation;
	GLuint m_texture;
};

