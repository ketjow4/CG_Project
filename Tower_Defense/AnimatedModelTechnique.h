#pragma once

#include "ModelTechnique.h"

class AnimatedModelTechnique : public ModelTechnique 
{
public:
	/** Maksymalna liczba koœci */
    static const uint MAX_BONES = 100;

    AnimatedModelTechnique();
	/**
	* Funkcja inicjalizuj¹ca shadery s³u¿ace do wyœwietlania modeli z animacj¹ szkieletow¹.
	*/
    virtual bool Init();

	/**
	* Funkcja przekazuj¹ca do shaderów transformacje danej koœci.
	*/
	void SetBoneTransform(uint Index, const Matrix4f& Transform);
private:
    GLuint m_boneLocation[MAX_BONES];
};
