#pragma once

#include "technique.h"
#include "math_3d.h"
#include "types.h"

class PickingTechnique : public Technique
{
public:
    PickingTechnique();
	/**
	* Funkcja inicjalizuj¹ca shadery pozwalaj¹ce na rzutowanie kursora myszy do œwiata gry.
	*/
    virtual bool Init();
	/**
	* Funkcja przekazuj¹ca do shaderów macierz WVP.
	*/
    void SetWVP(const Matrix4f& WVP);  
private:
    GLuint m_WVPLocation;
};


