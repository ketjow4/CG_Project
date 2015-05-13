#pragma once
#include <GL/glew.h>

class PickingTexture
{
public:
    PickingTexture();
    ~PickingTexture();
    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
    void EnableWriting();
    void DisableWriting();
    
    struct PixelInfo
	{
        float x;
        float y;
        float z;
        
        PixelInfo()
			: x(0.f), y(0.f), z(0.f)
        {}
    };

    PixelInfo ReadPixel(unsigned int x, unsigned int y);
    
private:
    GLuint m_fbo;
    GLuint m_pickingTexture;
    GLuint m_depthTexture;

	void FreeResources();
};

