#pragma once

#include "technique.h"
#include "math_3d.h"
#include "types.h"

class PickingTechnique : public Technique
{
public:
    PickingTechnique();
    virtual bool Init();
    void SetWVP(const Matrix4f& WVP);  
private:
    GLuint m_WVPLocation;
};


