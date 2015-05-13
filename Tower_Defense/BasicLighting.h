#ifndef LIGHTING_TECHNIQUE_H
#define	LIGHTING_TECHNIQUE_H

#include "technique.h"
#include "math_3d.h"



struct DirectionalLight
{
    Vector3f Color;
    float AmbientIntensity;
	Vector3f Direction;
    float DiffuseIntensity;
};


class BasicLightingTechnique : public Technique {
public:


    BasicLightingTechnique();

    virtual bool Init();

    void SetWVP(const Matrix4f& WVP);
	void SetWorldMatrix(const Matrix4f& WVP);
	void SetTextureUnit(unsigned int TextureUnit);
    void SetDirectionalLight(const DirectionalLight& Light);

private:

    GLuint m_WVPLocation;
    GLuint m_samplerLocation;
    GLuint m_WorldMatrixLocation;
    
	struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint Direction;
        GLuint DiffuseIntensity;
    } m_dirLightLocation;
};


#endif	/* LIGHTING_TECHNIQUE_H */
