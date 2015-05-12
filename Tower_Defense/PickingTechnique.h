#pragma once

#include "technique.h"
#include "math_3d.h"
#include "RenderCallbacks.h"
#include "types.h"

class PickingTechnique : public Technique, public IRenderCallbacks
{
public:

    PickingTechnique();

    virtual bool Init();

    void SetWVP(const Matrix4f& WVP);

    void SetObjectIndex(uint ObjectIndex);
    
    void DrawStartCB(uint DrawIndex);
    
private:
    
    GLuint m_WVPLocation;
    GLuint m_drawIndexLocation;
    GLuint m_objectIndexLocation;
};


