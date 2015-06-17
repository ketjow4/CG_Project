#pragma once

#include "ShadowTechnique.h"

class SimpleShadowTechnique : public ShadowTechnique
{
public:
	SimpleShadowTechnique();
	~SimpleShadowTechnique();
	/**
	* Funkcja inicjalizuj¹ca shadery s³u¿ace do wyœwietlania cieni statycznych obiektów.
	*/
    virtual bool Init();
};

