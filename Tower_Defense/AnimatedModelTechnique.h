#pragma once

#include "ModelTechnique.h"

class AnimatedModelTechnique : public ModelTechnique 
{
public:
	/** Maksymalna liczba ko�ci */
    static const uint MAX_BONES = 100;

    AnimatedModelTechnique();
	/**
	* Funkcja inicjalizuj�ca shadery s�u�ace do wy�wietlania modeli z animacj� szkieletow�.
	*/
    virtual bool Init();

	/**
	* Funkcja przekazuj�ca do shader�w transformacje danej ko�ci.
	*/
	void SetBoneTransform(uint Index, const Matrix4f& Transform);
private:
    GLuint m_boneLocation[MAX_BONES];
};
