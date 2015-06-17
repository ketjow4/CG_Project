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
	* Funkcja inicjalizuj�ca shadery s�u�ace do wy�wietlania grafik 2d.
	*/
	virtual bool Init();
	/**
	* Funkcja przekazuj�ca do shader�w macierz WVP.
	*/
	void SetWVP(const Matrix4f& WVP);
	/**
	* Funkcja rysuje prostok�t.
	* @param x wsp�rz�dna x pocz�tku prostok�ta
	* @param y wsp�rz�dna y pocz�tku prostok�ta
	* @param width szeroko�� prostok�ta
	* @param height wysoko�� prostok�ta
	* @param isTex 1 je�li chcemy oteksturowa� prostok�t
	* @param tex tekstura prostokata
	* @param color kolor prostokat�
	*/
	void RenderQuad(int x,int y, int width, int height, int isTex, Texture* tex, Vector3f color = Vector3f(1,1,1));
private:
	GLuint VAO,VBO;
	GLuint m_WVPLocation;
	GLuint m_ColorLocation;
	GLuint m_texture;
};

