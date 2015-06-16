#pragma once
#include <GL/glew.h>

class PickingTexture
{
public:
    PickingTexture();
    ~PickingTexture();
	/**
	* Funkcja inicjalizuj�ca obiekt obs�uguj�cy bufor pozycji potrzebny do rzytowania kursora myszy do �wiata gry.
	* @param WindowWidth szeroko�� okna programu
	* @param WindowHeight wysoko�� okna programu
	*/
    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
	/**
	* Funkcja umo�liwia zapis do bufora pozycji.
	*/
    void EnableWriting();
	/**
	* Funkcja blokuje zapis do bufora pozycji.
	*/
    void DisableWriting();
    
    struct PixelInfo
	{
        float x;
        float y;
        float z;
        
        PixelInfo()
			: x(0.f), y(0.f), z(0.f)
        {}
    };

	/**
	* Funkcja odczytuje pozycj� punktu ze �waita gry widocznego w oknie aplikacji.
	* @param x wsp�rzedna x na oknie aplikacji
	* @param y wsp�rzedna y na oknie aplikacji
	*/
    PixelInfo ReadPixel(unsigned int x, unsigned int y);
private:
    GLuint m_fbo;
    GLuint m_pickingTexture;
    GLuint m_depthTexture;

	void FreeResources();
};

