#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H  
#include <iostream>
#include <map>
#include <string>
#include "Technique.h"
#include "glm\glm.hpp"
#include "math_3d.h"
#include "GameConstsDefinitions.h"

struct Character 
{
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
    GLuint Advance;     // Horizontal offset to advance to next glyph
};

class Text : public Technique
{
public:
	/** Szeroko�� okna */
	float screenWidth;
	/** Wysoko�� okna */
	float screenHeight;
	/** Rozmiar czcionki */
	int fontSize;

	Text(int fontSize);
	~Text();
	/**
	* Funkcja wy�wietla podany tekst.
	* @param text tekst do wy�wietlenia
	* @param x wsp�rzedna x pocz�tku wy�wietlanego tekstu
	* @param y wsp�rzedna y pocz�tku wy�wietlanego tekstu
	* @param scale ws��pczynnik skaluj�cy tekst
	* @param color kolor tekstu
	*/
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
private:
	std::map<GLchar, Character> Characters;
	GLuint VAO, VBO;

};

