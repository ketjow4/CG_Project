#pragma once

#include "Technique.h"
#include "math_3d.h"
#include "types.h"

class PickingTechnique : public Technique
{
public:
    PickingTechnique();
	/**
	* Funkcja inicjalizująca shadery pozwalające na rzutowanie kursora myszy do świata gry.
	*/
    virtual bool Init();
	/**
	* Funkcja przekazująca do shaderów macierz WVP.
	*/
    void SetWVP(const Matrix4f& WVP);  
private:
    GLuint m_WVPLocation;
};


