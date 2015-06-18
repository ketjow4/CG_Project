#include "Drawing2D.h"


Drawing2D::Drawing2D(void)
{
}


Drawing2D::~Drawing2D(void)
{
}


bool Drawing2D::Init()
{
    if (!Technique::Init()) 
        return false;

    if (!AddShader(GL_VERTEX_SHADER, "Shaders/drawing2d.vs")) 
        return false;

    if (!AddShader(GL_FRAGMENT_SHADER, "Shaders/drawing2d.fs")) 
        return false;

    if (!Finalize()) 
        return false;

	m_WVPLocation = GetUniformLocation("gWVP");
	m_ColorLocation = GetUniformLocation("m_Color");
	m_texture = GetUniformLocation("isTex");


	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

void Drawing2D::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);    
}

//if there is texture set isTex to 1 else set this to 0 if there is no texture you can pass null
void Drawing2D::RenderQuad(int x,int y, int width, int height, int isTex, Texture* tex, Vector3f color )
{
	Enable();

	double screenWidth = 640.0;
	double screenHeight = 480.0;
	Matrix4f mat = Matrix4f(2.0 / (screenWidth - 0.0), 0, 0, -(screenWidth + 0.0) / (screenWidth - 0.0), 0, 2.0 / (screenHeight - 0.0), 0, -(screenHeight + 0) / (screenHeight - 0), 0, 0, -2.0 / (1.0 + 1.0), -(1.0 - 1.0) / (1.0 + 1.0), 0, 0, 0, 1);


	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)mat); 
	glUniform3f(m_ColorLocation, (GLfloat)color.x, (GLfloat)color.y, (GLfloat)color.z);
	glUniform1i(m_texture, isTex);
	//draw2D.SetWVP(mat);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

		GLfloat vertices[6][4] = {
				{ x, y + height, 0.0, 0.0 },
				{ x, y, 0.0, 1.0 },
				{ x + width, y, 1.0, 1.0 },

				{ x, y + height, 0.0, 0.0 },
				{ x + width, y, 1.0, 1.0 },
				{ x + width, y + height, 1.0, 0.0 }
		};
		
		if(tex != NULL && isTex == 1)
			tex->Bind(GL_TEXTURE0);

		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
}