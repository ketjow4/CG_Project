#ifndef TEXT_H
#define TEXT_H

#include <ft2build.h>
#include FT_FREETYPE_H  

#include <iostream>
#include <map>
#include <string>

#include "technique.h"
#include "glm\glm.hpp"
#include "math_3d.h"

struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};



class Text : public Technique
{
public:
	Text(int fontSize);
	~Text();

	
	std::map<GLchar, Character> Characters;
	GLuint VAO, VBO;

	float screenWidth, screenHeight;
	int fontSize;

	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);


private:

};





#endif