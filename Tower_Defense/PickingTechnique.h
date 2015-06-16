#pragma once

#include "technique.h"
#include "math_3d.h"
#include "types.h"

class PickingTechnique : public Technique
{
public:
    PickingTechnique();
	/**
	* Funkcja inicjalizuj�ca shadery pozwalaj�ce na rzutowanie kursora myszy do �wiata gry.
	*/
    virtual bool Init();
	/**
	* Funkcja przekazuj�ca do shader�w macierz WVP.
	*/
    void SetWVP(const Matrix4f& WVP);  
private:
    GLuint m_WVPLocation;
};


