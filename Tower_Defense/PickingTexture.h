#pragma once
#include <GL/glew.h>

class PickingTexture
{
public:
    PickingTexture();
    ~PickingTexture();
	/**
	* Funkcja inicjalizuj¹ca obiekt obs³uguj¹cy bufor pozycji potrzebny do rzytowania kursora myszy do œwiata gry.
	* @param WindowWidth szerokoœæ okna programu
	* @param WindowHeight wysokoœæ okna programu
	*/
    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
	/**
	* Funkcja umo¿liwia zapis do bufora pozycji.
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
	* Funkcja odczytuje pozycjê punktu ze œwaita gry widocznego w oknie aplikacji.
	* @param x wspó³rzedna x na oknie aplikacji
	* @param y wspó³rzedna y na oknie aplikacji
	*/
    PixelInfo ReadPixel(unsigned int x, unsigned int y);
private:
    GLuint m_fbo;
    GLuint m_pickingTexture;
    GLuint m_depthTexture;

	void FreeResources();
};

