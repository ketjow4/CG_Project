#pragma once

#include "ShadowTechnique.h"

class SimpleShadowTechnique : public ShadowTechnique
{
public:
	SimpleShadowTechnique();
	~SimpleShadowTechnique();
	/**
	* Funkcja inicjalizuj�ca shadery s�u�ace do wy�wietlania cieni statycznych obiekt�w.
	*/
    virtual bool Init();
};

