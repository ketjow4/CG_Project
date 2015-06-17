#pragma once

#include "Technique.h"
#include "math_3d.h"
#include "texture.h"

class Drawing2D : public Technique
{
public:
	Drawing2D(void);
	~Drawing2D(void);


	virtual bool Init();

	void SetWVP(const Matrix4f& WVP);

	void RenderQuad(int x,int y, int width, int height, int isTex, Texture* tex, Vector3f color = Vector3f(1,1,1));

private:
	GLuint VAO,VBO;

	GLuint m_WVPLocation;
	GLuint m_ColorLocation;
	GLuint m_texture;

};
