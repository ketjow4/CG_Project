#pragma once

#include "ShadowTechnique.h"

class SimpleShadowTechnique : public ShadowTechnique
{
public:
	SimpleShadowTechnique();
	~SimpleShadowTechnique();
	/**
	* Funkcja inicjalizująca shadery służace do wyświetlania cieni statycznych obiektów.
	*/
    virtual bool Init();
};

