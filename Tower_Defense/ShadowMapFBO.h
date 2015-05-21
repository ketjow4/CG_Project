#ifndef SHADOWMAPFBO_H
#define	SHADOWMAPFBO_H

#include <GL/glew.h>
#include <stdio.h>

class ShadowMapFBO
{
public:
	ShadowMapFBO(void);
	~ShadowMapFBO(void);
	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
    void BindForWriting();
    void BindForReading(GLenum TextureUnit);
private:
    GLuint m_fbo;
    GLuint m_shadowMap;

	void FreeResources();
};

#endif	/* SHADOWMAPFBO_H */
