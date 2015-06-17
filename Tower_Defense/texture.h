#pragma once

#include <string>

#include <GL/glew.h>
#include <Magick++.h>

class Texture
{
public:
	/**
	* Tworzy teksturê na podstawie pliku.
	* @param Filename
	*/
    Texture(GLenum TextureTarget, const std::string& Filename);
	/**
	* Funkcja ³aduje teksturê z pliku.
	*/
    bool Load();
	/**
	* Funkcja wi¹¿e teskture z identyfikatorem.
	*/
    void Bind(GLenum TextureUnit);
private:
    std::string m_filename;
    GLenum m_textureTarget;
    GLuint m_textureObj;
    Magick::Image m_image;
    Magick::Blob m_blob;
};

