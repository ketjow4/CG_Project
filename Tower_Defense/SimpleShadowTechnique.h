#pragma once

#include "ShadowTechnique.h"

class SimpleShadowTechnique : public ShadowTechnique
{
public:
	SimpleShadowTechnique();
	~SimpleShadowTechnique();
    virtual bool Init();
};

