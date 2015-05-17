#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 m_Color;
uniform int isTex;

void main()
{    
	if(isTex != 0)
	{
		color = texture2D(text, TexCoords) * vec4(m_Color, 1.0);
	}
	else
	{
		color = vec4(m_Color, 1.0);
	}
}  